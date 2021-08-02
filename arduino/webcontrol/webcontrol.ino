

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

#define TOBOOLSTR(v) v ? "true" : "false"

#define SSID "***"
#define PASSWORD "***"
#define TELEGRAMID "***"

#define MSAPIN A0 // Moisture sensor analog pin
#define MSDPIN D0 // Moisture sensor digital pin
#define MTRPIN D1 // Motor pin

#define STATUSURL "http://flows.messagebird.com/flows/***/invoke"

// Minimum delay between status updates
#define STATUSMINDELAY 60000

unsigned long lastStatusTime;

bool pumpOn;
unsigned long pumpOffTime;

HTTPClient client;
ESP8266WebServer server(80);

void setup() {
  pinMode(MSAPIN, INPUT);
  pinMode(MSDPIN, INPUT);
  pinMode(MTRPIN, OUTPUT);
  
  Serial.begin(115200);

  // Connect to WiFi
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

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  setupServer();
  
}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
  delay(500);
  
  double msa = analogRead(MSAPIN);
  if (msa < 1000 && lastStatusTime < millis() ) {  
    if(WiFi.status()== WL_CONNECTED){

      // Data to send with HTTP POST
      char data[100];
      sprintf(data,"{\"text\": \"%f\",\"telegramid\": \"%s\"}", msa, TELEGRAMID);
      String httpRequestData = String(data);
      
      client.begin(STATUSURL);
      client.addHeader("Content-Type", "application/json");
      int httpResponseCode = client.POST(httpRequestData);
      client.end();

      if (httpResponseCode != 204) {
        Serial.printf("Error sending to %s", STATUSURL);
      }
      lastStatusTime = millis() + STATUSMINDELAY;  
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
    startPump(30000);
  }
  
  // Check if it's time to turn of the pump
  if (pumpOn && pumpOffTime < millis()) {
    stopPump();
  }
}


void setupServer() {
  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/startpump", HTTP_POST, handleStartPump);
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void handleRoot() {
  server.sendHeader("Location", "/status");
  server.send(302);
}

void handleStatus() {
  char data[100];
  double msa = analogRead(MSAPIN);
  Serial.println((pumpOffTime - millis())/1000);
  sprintf(data, "{\n\t\"moisture\": \"%f\",\n\t\"pumpOn\": %s,\n\t\"pumpOffTime\": %d\n}", msa, TOBOOLSTR(pumpOn), pumpOn ? (pumpOffTime - millis())/1000 : 0);
  server.send(200, "application/json", data);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleStartPump() {
  Serial.println("handleStartPump()");
  startPump(30000);
  server.send(200, "text/plain", "Pump Started");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}




void startPump(long timer) {
  pumpOn = true;
  digitalWrite(MTRPIN,1);
  pumpOffTime = millis() + timer;
}

void stopPump() {
  pumpOn = false;
  digitalWrite(MTRPIN,0);
  pumpOffTime = millis();
}
