//Libraries
#include <ArduinoJson.h>
#include <Arduino_JSON.h>
#include <JSON.h>
#include <JSONVar.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//Pins
#define ANA A0
#define POMPOUT D6
#define LED D0
#define SENSORPOWER D1

//Passwords
#define SSID "your-wifi-ssid" // Add your WiFi SSID Here
#define PASSWORD "your-wifi-password" // Add your Wifi password Here

//Settings 
String urlWebhookData = "your-googlesheet-webhook-url";
String urlWebhookNotification = "your-notification-webhook-url";
double analogValue = 0.0;
int amountOfMeasurements = 10; //how many times to measure
int pumpTime = 5000; // how long it should pump in miliseconds
int threshhold = 400; //your analog value threshold
int sleepTime = 1800e6; //sleep time an hour, time in microseconds, beware to not set this higher than 71 minutes. https://thingpulse.com/max-deep-sleep-for-esp8266/#:~:text=%E2%80%A6the%20maximum%20value%20for%20a,appears%20to%20be%20~71%20minutes.
String pumpStatus = "";


// There are a few things you need to change in the wiring so make sure you checkout the readme :) 
void setup() {
  //start serial
  Serial.begin(115200);
  Serial.setTimeout(2000);
  
  //set pinmodes
  pinMode(ANA, INPUT);
  pinMode(POMPOUT, OUTPUT);
  pinMode(SENSORPOWER, OUTPUT);

  analogValue = 0; //reset analogValue

  
  digitalWrite(SENSORPOWER, HIGH); //Power on sensor and wait a bit to start
  delay(2000);

 
  for (int i = 0; i < amountOfMeasurements; i++){  // Measure multiple times
    analogValue = analogValue + analogRead(ANA);
    delay(200);
  }
  digitalWrite(SENSORPOWER, LOW); //Turn off power sensor
  analogValue = analogValue / amountOfMeasurements; //average measurement
  Serial.println("The avarage measure is: ");
  Serial.println(analogValue);


  if (analogValue > threshhold) { //start pumping if value > threshold
    digitalWrite(POMPOUT, HIGH);
    pumpStatus = "Did Pump"; //set pumpstatus
    delay(pumpTime);  //delay for pumptime
    digitalWrite(POMPOUT, LOW);
  } else {
    pumpStatus = "Did not pump";
    digitalWrite(POMPOUT, LOW);
  }

  Serial.println(pumpStatus); 

 
  WiFi.begin(SSID, PASSWORD); //begin wifi connection
  Serial.println("Connecting");
  bool tryingToConnect = true; //set boolean that wifi is connecting

  while(tryingToConnect){ //while connecting
    delay(500);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED){ //if connected set bool to false, so we can continue
      tryingToConnect = false; 
    } else if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL){ 
      //if error dont send anything, wifi might be down, better luck next time
      ESP.deepSleep(sleepTime); 
    }
  }

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  if (analogValue > threshhold){ //send notification
    HTTPClient http;
    http.begin(urlWebhookNotification); //set url
    http.addHeader("Content-Type", "application/json"); //add http header, this is needed to send json
    DynamicJsonDocument doc(2048); //create a json object
    doc["value1"] = analogValue; //Here you can add your values to the json
    String json; //make string variable to store json
    serializeJson(doc, json); //put DynamicJsonObject in string
    int httpCode = http.POST(json); //make the http post request and save the http code
    Serial.println(http.getString()); //print the response
    Serial.println(httpCode); // print the respose code, most of the time 200 is ok
    http.end(); 
  }

  //same process as above
  HTTPClient http;
  http.begin(urlWebhookData);
  http.addHeader("Content-Type", "application/json");
  DynamicJsonDocument doc(2048);
  doc["value1"] = analogValue;
  doc["value2"] = pumpStatus;
  doc["value3"] = "";
  String json;
  serializeJson(doc, json);
  int httpCode = http.POST(json);
  Serial.println(http.getString());
  Serial.println(httpCode);
  http.end();

  Serial.println("I am now going to sleep for: "); 
  Serial.print(sleepTime);
  Serial.print(" seconds");
  ESP.deepSleep(sleepTime); //sleeping
  
}
void loop() {
}
