#define ANA A0
#define DIGI D5
#define POMPOUT D6
double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
  Serial.begin(115200);
  Serial.println("Paolo Test");
}
void loop() {
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  // Serial data
  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);
  Serial.println(" ");
  if (digitalValue == 0) {
    digitalWrite(POMPOUT, false);
  } else {
        Serial.println("PUMPIN");
      digitalWrite(POMPOUT, true);
  }
  delay(1000);
}
