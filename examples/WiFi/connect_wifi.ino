#include <ESP8266WiFi.h>

#define SSID "***" // Add your WiFi SSID Here
#define PASSWORD "***" // Add your Wifi password Here

void setup() {
  Serial.begin(115200);

  WiFi.begin(SSID, PASSWORD);
  Serial.println("Connecting");
  
  // Wait for Wifi to connect
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}