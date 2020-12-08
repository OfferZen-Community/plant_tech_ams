#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);

  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  Serial.print("Number of available WiFi networks discovered:");
  Serial.println(numSsid);
    
  for (byte a =0; a<numSsid;a++) {
    Serial.print("SSID: ");
    Serial.print(WiFi.SSID(a));
    Serial.print(" Signal: ");
    Serial.println(WiFi.RSSI(a));
  }
}

void loop() {}