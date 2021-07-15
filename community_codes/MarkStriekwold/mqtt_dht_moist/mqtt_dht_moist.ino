#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>
#include "DHTesp.h" 

#define WIFI_SSID "<SSID>"
#define WIFI_PASSWORD "<PASSWORD>"
// #define MQTT_HOST IPAddress(192, 168, 1, XXX)
#define MQTT_HOST "<PI_SERVER>"
#define MQTT_PORT 1883
// MQTT Topics
#define MQTT_PUB_TEMP "dht/temp"
#define MQTT_PUB_HUM "dht/hum"
#define MQTT_MOIST "moist"
#define MQTT_PUMP "pump"

static const int dry = 715; // value for dry sensor
static const int wet = 288; // value for wet sensor

// Digital pin connected to the DHT sensor
#define DHTPIN      D3
#define DHTSWITCH   D2
#define MOISTPIN    A0
#define MOISTSWITCH D1
#define PUMPPIN     D6

// Initialize DHT sensor
DHTesp dht;

// Variables to hold sensor readings
float temp;
float hum;
int   percentageHumidity;
int   sensorVal;

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 10000;        // Interval at which to publish sensor readings

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe(MQTT_PUMP, 1);
  Serial.print("Subscribing at QoS 1, packetId: ");
  Serial.println(packetIdSub);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttPublish(uint16_t packetId) {
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  String s = String(payload).substring(0,len);
  if(s == "ON"){
    digitalWrite(PUMPPIN, LOW); 
    Serial.println("ON");
  } else {
    digitalWrite(PUMPPIN, HIGH); 
    Serial.println("OFF");
  }
}

void pubMoisture(){
    digitalWrite(MOISTSWITCH, HIGH);
    delay(100);
    sensorVal = analogRead(MOISTPIN);
    Serial.printf("Sensorval: %i \n", sensorVal);
    digitalWrite(MOISTSWITCH, LOW);
    percentageHumidity = map(sensorVal, wet, dry, 100, 0); 
    // Publish an MQTT message on topic moist
    uint16_t packetIdPub0 = mqttClient.publish(MQTT_MOIST, 1, true, String(percentageHumidity).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_MOIST, packetIdPub0);
    Serial.printf("Message: %i \n", percentageHumidity);  
}

void pubDHT(){
    digitalWrite(DHTSWITCH, HIGH);
    //bug DHT11 = 1000 else 2000 
    delay(dht.getMinimumSamplingPeriod()*2);
    // DHT sensor readings
    hum = dht.getHumidity();
    Serial.printf("Hum: %.2f \n", hum);  
    // Read temperature as Celsius (the default)
    temp = dht.getTemperature();
    Serial.printf("Temp: %.2f \n", temp);

    digitalWrite(DHTSWITCH, LOW);

    // Publish an MQTT message on topic dht/temp
    uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(temp).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_TEMP, packetIdPub1);

    // Publish an MQTT message on topic dht/hum
    uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_HUM, 1, true, String(hum).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId %i: ", MQTT_PUB_HUM, packetIdPub2);
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  dht.setup(DHTPIN, DHTesp::DHT11);

  pinMode(PUMPPIN, OUTPUT);
  pinMode(DHTSWITCH, OUTPUT);
  pinMode(MOISTSWITCH, OUTPUT);

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  //mqttClient.setCredentials("REPlACE_WITH_YOUR_USER", "REPLACE_WITH_YOUR_PASSWORD");
  
  connectToWifi();
}

void loop() {
  unsigned long currentMillis = millis();
  // Every X number of seconds (interval = 10 seconds) 
  // it publishes a new MQTT message
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    pubMoisture();
    pubDHT();
  }
}
