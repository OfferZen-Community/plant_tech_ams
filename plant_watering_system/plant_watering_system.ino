#include <DHT.h>

#define ANA A0
#define DIGI D5
#define POMPOUT D6
#define SENSOR D7
#define DHTTYPE    DHT22      // DHT 22 (AM2302) Could be swapped for DHT 11

double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;
// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;
unsigned long previousMillis = 0;    // will store last time DHT was updated
const long interval = 2000;

DHT dht(SENSOR, DHTTYPE); 

void displayDHTDetails(){
  // Read temperature as Celsius (the default)
  float newT = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float newT = dht.readTemperature(true);
  // if temperature read failed, don't change the value
  if (isnan(newT)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    t = newT;
    Serial.println(t);
  }
  // Read Humidity
  float newH = dht.readHumidity();
  // if humidity read failed, don't change h value 
  if (isnan(newH)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  else {
    h = newH;
    Serial.println(h);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
  pinMode(SENSOR, OUTPUT);
  digitalWrite(SENSOR, LOW);
  Serial.begin(115200);
  dht.begin();
  Serial.println("Paolo Test");
}

void loop() {
  unsigned long currentMillis = millis(); //We check the milliseconds each time so that we only read the sensor every <interval> seconds.
  if (currentMillis - previousMillis >= interval) {
    digitalWrite(SENSOR, HIGH);
    previousMillis = currentMillis;
    displayDHTDetails();
    analogValue = analogRead(ANA);
    digitalValue = digitalRead(DIGI);
    digitalWrite(SENSOR, LOW);
    // Serial data
    Serial.print("Analog raw: ");
    Serial.println(analogValue);
    Serial.print("Digital raw: ");
    Serial.println(digitalValue);
    Serial.println(" ");
    if (analogValue < 1024) {
      digitalWrite(POMPOUT, false);
    } else {
        Serial.println("PUMPIN");
        //0digitalWrite(POMPOUT, true);
    }
  }
  yield();
} 
