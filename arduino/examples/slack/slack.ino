#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>
// WiFi parameters to be configured
const char* ssid = "***";
const char* password = "***";
String url = "/services/***Your webhook here***";
const char* host = "hooks.slack.com";
const int httpsPort = 443;
// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "C1 0D 53 49 D2 3E E5 2B A2 61 D5 9E 6F 99 0D 3D FD 8B B2 B3";
ESP8266WebServer server(80);
WiFiClientSecure client;
#define ANA A0
#define DIGI D5
#define POMPOUT D6
double analogValue = 0.0;
int digitalValue = 0;
void setup(void)
{ 
  Serial.begin(115200);
  setupPump();
  // Connect to WiFi
  WiFi.begin(ssid, password);
  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  setupServer();
}
void loop() {
  server.handleClient();
  delay(500);
}
void setupServer() {
  server.on("/", HTTP_GET, handleStatus);
  server.on("/message", HTTP_GET, sendMessage);
  server.on("/pump/on", HTTP_GET, pumpOn);
  server.on("/pump/off", HTTP_GET, pumpOff);
  server.onNotFound(handleStatus);
  server.begin();
  Serial.println("HTTP server started");
}
void setupClient() {
  client.setFingerprint(fingerprint);
  //Setting the fingerprint is better but for just quickly testing it's sometimes useful to setInsecure instead.
  //client.setInsecure();
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.println("connection established");
  }
}
void setupPump() {
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
}
void handleStatus() {
  char data[100];
//  double msa = analogRead(MSAPIN);
   analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  sprintf(data, "{\"moisture\": {\"analog\":%f, \"digital\": %f}}", analogValue, digitalValue);
  server.send(200, "application/json", data);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}
void sendMessage() {
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  char data[100];
  sprintf(data, "{\"text\": \"analog :%f, digital: %f\"}\r\n", analogValue, digitalValue);
  Serial.println(data);
  Serial.println(strlen(data));
  Serial.println(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "User-Agent: ArduinoIoT/1.0\r\n" +
                   "Connection: close\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: "+ strlen(data) + "\r\n\r\n" +
                   data
                );
  setupClient();
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "User-Agent: ArduinoIoT/1.0\r\n" +
                   "Connection: close\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: "+ strlen(data) + "\r\n\r\n" +
                   data
                  );
   Serial.println(client.readString());
   //It's important to stop the client otherwise the connection will be left open. Subsequent requests on the same client will not work.
   client.stop();
   server.send(200, "application/json", data);
}
void pumpOn() {
  Serial.println("PUMPIN");
  digitalWrite(POMPOUT, true);
  server.send(200, "application/json", "{\"pump\":true}");
  delay(1000);
}
void pumpOff() {
  Serial.println("PUMPOUT");
  digitalWrite(POMPOUT, false);
  server.send(200, "application/json", "{\"pump\":false}");
  delay(1000);
}
