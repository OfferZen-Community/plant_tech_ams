#define ANA A0
#define DIGI D5
#define SENSOR D7

double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(SENSOR, OUTPUT);
  Serial.begin(115200);
  Serial.println("Test");
}

void loop() {
  digitalWrite(SENSOR, HIGH);
  delay(100);
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  digitalWrite(SENSOR, LOW);
  // Serial data
  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);
  Serial.println(" ");
  delay(1000);
}
