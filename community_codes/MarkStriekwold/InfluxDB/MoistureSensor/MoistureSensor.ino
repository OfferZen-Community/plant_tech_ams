#include <ESP8266WiFiMulti.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"

#define ANA A0
#define DIGI D5
#define SENSOR1 D7
// WiFi AP SSID
#define WIFI_SSID "<SSID>"
// WiFi password
#define WIFI_PASSWORD "<PASSWORD>"
// InfluxDB v2 server url, e.g. https://eu-central-1-1.aws.cloud2.influxdata.com (Use: InfluxDB UI -> Load Data -> Client Libraries)
#define INFLUXDB_URL "<URL>"
// InfluxDB v2 server or cloud API authentication token (Use: InfluxDB UI -> Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "<TOKEN>"
// InfluxDB v2 organization id (Use: InfluxDB UI -> User -> About -> Common Ids )
#define INFLUXDB_ORG "<ORG>"
// InfluxDB v2 bucket name (Use: InfluxDB UI ->  Data -> Buckets)
#define INFLUXDB_BUCKET "<BUCKET>"

// Set timezone string according to https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
Point sensor("MOISTURE");

double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(SENSOR1, OUTPUT);
  Serial.begin(115200);
  Serial.println("Test");
  // Setup wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Accurate time is necessary for certificate validation and writing in batches
  // For the fastest time sync find NTP servers in your area: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  // Clear fields for reusing the point. Tags will remain untouched
  sensor.clearFields();

  digitalWrite(SENSOR1, HIGH);
  delay(100);
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  digitalWrite(SENSOR1, LOW);
  // Serial data
  sensor.addField("analog", analogValue);
  sensor.addField("digital", digitalValue);
  //sensor.addField("temperature", temperature);

  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);
  Serial.println(" ");
  
  Serial.print("Writing: ");
  Serial.println(sensor.toLineProtocol());
  
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  //Wait 10s
  Serial.println("Wait 10s");
  delay(10000);
}
