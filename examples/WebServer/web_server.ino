

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

#define SSID "***" // Add your WiFi SSID Here
#define PASSWORD "***" // Add your Wifi password Here
#define PORT 80

ESP8266WebServer server(PORT); // Port for webserver

void setup() {
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

  setupServer();
  
}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
  delay(500);
}

void setupServer() {
  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void handleRoot() {
  server.send(200, "text/plain", "Hello from Make");
}
