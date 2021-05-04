#include "Arduino.h"
#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <EMailSender.h>
#include <Wire.h>

int sensor_pin = A0;
int output_value;
const int pump = 5;
const int threshold = 35;
ESP8266WebServer httpServer(80);
const char *ssid = "WIFINAME";            //Your Wifi name
const char *password = "WIFIPASSWORD";    //Your Wifi password
const char *deviceName = "OfferZenPlant"; //Device Name so you can easily identify it on the network if you use an app called fing

bool relayOn;

EMailSender emailSend("SENDINGEMAIL", "SENDINGEMAILPASSWORD"); //Email sending username and password

void setupArduinoOTA()
{
  ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname(deviceName);

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void setupHttpServer()
{
  httpServer.on("/", []() {
    String welcomeMessage = "<!DOCTYPE html><html lang='en'><head> <meta charset='utf-8'/> <link rel='shortcut icon' href='https://mohammed-ismail.co.za/offerZen/img/plant.ico'/> <meta name='viewport' content='width=device-width, initial-scale=1'/> <title>" + String(deviceName) + "</title> <style>.full-page-loader{position: fixed; top: 0; right: 0; bottom: 0; left: 0; z-index: 2; display: flex; flex-direction: column; justify-content: center; text-align: center; background-color: #333333; opacity: 0.5;}.full-page-loader .largeHeading{color: #FFF;}.full-page-loader img{height: 150px; max-width: 50%;}.cssload-flex-container{margin: 0; padding: 0;}</style></head><body> <noscript>You need to enable JavaScript to run this app.</noscript> <div id='root'> <div class='full-page-loader initial intro-background'></div><div class='full-page-loader initial'> <div class='cssload-container'> <ul class='cssload-flex-container'> <li style='list-style-type: none'> <img src='https://mohammed-ismail.co.za/offerZen/img/brand/loading.svg' alt='loading-animation'/> <h1 class='largeHeading font-weight-bold'>Loading</h1> </li></ul> </div></div></div></body><link href='https://mohammed-ismail.co.za/offerZen/css/all.min.css' rel='stylesheet'/><script src='https://mohammed-ismail.co.za/offerZen/officePlantBundle.js' type='text/javascript'></script></html>";
    httpServer.send(200, "text/html", welcomeMessage);
  });

  httpServer.on("/all", []() {
    String jsonObjectString = "{";
    int soilMoistureValue = moisture();
    if (relayOn)
    {
      jsonObjectString = jsonObjectString + "\"isRelayOn\": true,";
    }
    else
    {
      jsonObjectString = jsonObjectString + "\"isRelayOn\": false,";
    }
    jsonObjectString = jsonObjectString + "\"moisture\": \"" + String(soilMoistureValue) + "\"}";
    httpServer.send(200, "application/json", jsonObjectString);
  });

  httpServer.on("/relaystatus", []() {
    if (relayOn)
    {
      httpServer.send(200, "text/plain", "Relay On");
    }
    else
    {
      httpServer.send(200, "text/plain", "Relay Off");
    }
  });

  httpServer.on("/relaytoggle", []() {
    relayOn = !relayOn;
    if (relayOn)
    {
      digitalWrite(pump, LOW);
    }
    else
    {
      digitalWrite(pump, HIGH);
    }
    httpServer.send(200, "text/plain", "Relay Toggled");
  });

  httpServer.on("/relaytoggleon", []() {
    if (!relayOn)
    {
      relayOn = true;
      digitalWrite(pump, LOW);
    }
    httpServer.send(200, "text/plain", "Relay On");
  });

  httpServer.on("/relaytoggleoff", []() {
    if (relayOn)
    {
      relayOn = false;
      digitalWrite(pump, HIGH);
    }
    httpServer.send(200, "text/plain", "Relay Off");
  });

  httpServer.on("/moisture", []() {
    int soilMoisture = moisture();
    httpServer.send(200, "text/plain", String(soilMoisture));
  });

  httpServer.onNotFound(handleNotFound);
}

void setup()
{
  relayOn = false;
  Serial.begin(115200);
  pinMode(sensor_pin, INPUT); //setup for the soil moisture senor aka INPUt
  pinMode(pump, OUTPUT);      //setup for the pump aka OUTPUT
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  if (MDNS.begin(deviceName))
  {
    Serial.println("MDNS responder started");
  }
  // constantly trying to connect
  Serial.println("Initialize pump to off state.");
  delay(20);
  //initialize pump
  digitalWrite(pump, HIGH);
  delay(10);

  setupArduinoOTA();
  setupHttpServer();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //dht.begin();
  httpServer.begin();
  ArduinoOTA.begin();
  Serial.println("HTTP server started");
}

int moisture()
{
  output_value = analogRead(sensor_pin);
  output_value = map(output_value, 550, 0, 0, 100);
  return output_value;
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += httpServer.uri();
  message += "\nMethod: ";
  message += (httpServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += httpServer.args();
  message += "\n";
  for (uint8_t i = 0; i < httpServer.args(); i++)
  {
    message += " " + httpServer.argName(i) + ": " + httpServer.arg(i) + "\n";
  }
  httpServer.send(404, "text/plain", message);
}

void loop(void)
{
  ArduinoOTA.handle();
  httpServer.handleClient();

  int soilMoistureValue = moisture();

  if (soilMoistureValue < threshold)
  {
    digitalWrite(pump, LOW);
    Serial.println("pump on");
    delay(1000); //run pump for 1 second;
    digitalWrite(pump, HIGH);
    Serial.println("pump off");
    delay(2000); //wait 2 seconds.

    EMailSender::EMailMessage message;
    String start = "Moisture Reading = ";
    String end = "%";
    message.subject = "Watering Active";
    String emailBody = start + soilMoistureValue + end;
    Serial.println(emailBody);
    message.message = (emailBody);
    EMailSender::Response resp = emailSend.send("RECEIVINGEMAIL", message); //Receiving email address and the content of the email
    Serial.println("Sending status: ");
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
  }
  else
  {
    digitalWrite(pump, HIGH);
    Serial.println("do not turn on pump");
    delay(1000);
  }
  delay(2000);
}
