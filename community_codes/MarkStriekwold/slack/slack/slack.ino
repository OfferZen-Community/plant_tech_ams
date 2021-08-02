#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

String url = "/services/TXXXXXXXXXX/BXXXXXXXXXX/XXXXXXXXXXXXXXXXXXXXXXXX";
const char* host = "hooks.slack.com";
const int httpsPort = 443;

// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (Serial.available()>0)
  {
      String message = Serial.readString();
      int lengte = message.length()+11;
      Serial.println("requesting");
      client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "User-Agent: ArduinoIoT/1.0\r\n" +
                   "Connection: close\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: "+lengte+"\r\n\r\n" +
                   "{\"text\":\""+message+"\"}");
      Serial.println(client.readString());  
  }
}
