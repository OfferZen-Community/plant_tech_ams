#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// The pin header setup
#define SENSOR A0
#define PUMP D6

// Variables holding Sensor values and pump controls
double MoistureSensorA = 0.0;
double MoistureThreshold = 600.0; // threshold when the pump activates: higher means dryer
bool PumpAllowed = true;          // but only if enough time elapsed since the last time
bool PumpON = false;
int PumpTimerMax = 300000;         // how long will we wait until the next pump [ms]
int PumpTimerInit = 0;
int PumpingTime = 2500;           // for how long will the pump be pumping [ms]

// WiFi station setup
const char* ssidST = "Enter your Network Name Here";  // Enter SSID here
const char* passwordST = "Enter your WiFi Password Here";  //Enter Password here
int WiFiTry = 0;
bool WiFiIsAPmode = false;

// WiFi access point setup (fallback if no connection to router)
const char* ssidAP = "SelfWateringPlant_0001";  // Enter SSID here
const char* passwordAP = "This_Is_Awesome";  //Enter Password here

// Start web server on Port
ESP8266WebServer server(80);

void setup() {
  // Setup the pins
  pinMode(SENSOR, INPUT);
  pinMode(PUMP, OUTPUT);
  // serial connection for easier debugging
  Serial.begin(115200);
  Serial.println("Serial connection established...");
  // pull the pump low to disable it from the beginning
  digitalWrite(PUMP, false);

  // Connect to WiFi
  //connect to your local wi-fi network
  WiFi.begin(ssidST, passwordST);

  //check wi-fi is connected to given SSID; try 10 times
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED and WiFiTry <= 10) {
    WiFiTry += 1;
    delay(1000);
    Serial.print(".");
  }
  // check if we connected successfuly
  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println("");
    Serial.println("----");
    Serial.println("Successfuly connected to Wifi: " + String(ssidST));
    Serial.println("Got IP: ");  Serial.println(WiFi.localIP());
    Serial.println("----");
  } else { // otherwise, create an access point
    WiFiIsAPmode = true;
    Serial.println("");
    Serial.println("----");
    Serial.println("Could not connect to Wifi: " + String(ssidST));
    Serial.println("Setting up WiFi access point: " + String(ssidAP));
    // set ip address
    IPAddress local_ip(192, 168, 1, 1);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAP(ssidAP, passwordAP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
    Serial.println("----");
  }

  // Start the WebServer
  server.begin();
  Serial.println("HTTP server started");
  SetupWebServer();
}

void loop() {
  Serial.println("Connected " + String(WiFi.softAPgetStationNum()) + " Clients");

  // Server stuff
  server.handleClient();

  // read sensor
  MoistureSensorA = analogRead(SENSOR);

  // Serial data
  Serial.print("Analog raw: ");
  Serial.println(MoistureSensorA);
  Serial.print("Pump ON?: ");
  Serial.println(PumpON);
  Serial.print("Pump allowed: ");
  Serial.println(PumpAllowed);
  Serial.println(" ");

  // is the soil too dry? Water it if we are allowed (PumpTimerMax/1000 seconds passed since the last spill of water).
  if (MoistureSensorA >= MoistureThreshold and PumpON == false and PumpAllowed == true) {
    Serial.println("Too dry, watering...");
    PumpON = true;
    PumpAllowed = false;
    PumpTimerInit = millis();
    digitalWrite(PUMP, true);
    delay(PumpingTime);
    digitalWrite(PUMP, false);
    // or is everything fine?
  }
  
  // Did we water enough?
  if (MoistureSensorA < MoistureThreshold) {
    Serial.println("Soil moisture is OK!");
    PumpON = false;
    PumpAllowed = true;
    digitalWrite(PUMP, false);
  }

  // now check if PumpTimerMax/1000 seconds passed. If so, we allow watering again.
  if (PumpON and millis() - PumpTimerInit > PumpTimerMax) {
    PumpON = false;
    PumpAllowed = true;
  }
  
  // Its enough if we do that every 5 seconds.
  delay(5000);
}

// What comes next is the WebServer event handling and the styling of the Web Page.
// The SendHTML function will create a page according to the current sensor reading.
// It also adds a button to manually activate the pump.

void SetupWebServer() {
  server.on("/", handle_OnConnect);
  server.on("/pump", handle_pump);
  server.onNotFound(handle_NotFound);
}

void handle_OnConnect() {
  Serial.println("Web client connected!");
  server.send(200, "text/html", SendHTML(MoistureSensorA, PumpON));
}

void handle_pump() {
  Serial.println("Pump operating for a few seconds!");
  server.send(200, "text/html", SendHTML(MoistureSensorA, true));
  digitalWrite(PUMP, true);
  delay(PumpingTime);
  digitalWrite(PUMP, false);
}

String SendHTML(double sensor, bool pumping) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>SelfWateringPlant</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #FF5733;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>SelfWateringPlant Control Panel</h1>\n";
  
  if (WiFiIsAPmode) {
    ptr += "<h3>Using Access Point(AP) Mode</h3>\n";
  } else {
    ptr += "<h3>Connected to WiFi: " + String(ssidST) + "</h3>\n";
  }
  
  if (sensor < MoistureThreshold)
  {
    ptr += "<p>Moisture Status: GOOD</p><a class=\"button button-on\" href=\"/\">" + String(MoistureSensorA) + "</a>\n";
  }
  else
  {
    ptr += "<p>Moisture Status: DRY</p><a class=\"button button-off\" href=\"/\">" + String(MoistureSensorA) + "</a>\n";
  }

  if (pumping)
  {
    ptr += "<p>Pump Status: ON</p><a class=\"button button-off\" href=\"/\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>Pump Status: OFF</p><a class=\"button button-on\" href=\"/pump\">Switch ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handle_NotFound() {
  server.send(404, "text / plain", "Not found");
}
