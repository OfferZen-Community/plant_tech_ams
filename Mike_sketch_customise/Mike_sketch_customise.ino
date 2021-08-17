#define ANA A0
#define DIGI D5
#define POMPOUT D6
#define LED D4 // Use built-in LED which connected to D4 pin or GPIO 2
int pump_period = 4000;
int wait_period = 5000;
unsigned long runningtime;

double analogValue = 0.0;
int digitalValue = 0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;
void setup() 
{
  // put your setup code here, to run once:
  pinMode(ANA, INPUT);
  pinMode(DIGI, INPUT);
  pinMode(POMPOUT, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Mike Arduino setup");
 }
void loop() {
  analogValue = analogRead(ANA);
  digitalValue = digitalRead(DIGI);
  
  // Serial data
  Serial.print("Running Time(sec): ");
  runningtime = (millis()/1000); // running time in seconds
  Serial.println(runningtime);
  Serial.print("Analog raw: ");
  Serial.println(analogValue);
  Serial.print("Digital raw: ");
  Serial.println(digitalValue);

  // If soil is moist and running time >= 30 seconds, no pump
  if (analogValue <= 450 && runningtime >= 30) 
  {
    Serial.println("Moist - NOT PUMPIN");
    digitalWrite(POMPOUT, false);
    Serial.println("End of iteration");
    Serial.println(" ");
   } 
  // If soil is dry and running time >= 30 seconds, pump
  else if (analogValue > 450 && runningtime >= 30) 
  {
        Serial.println("Dry - PUMPIN with LED on");
        digitalWrite(POMPOUT, true); //pump on
        digitalWrite(LED, false); //turn on LED
        delay(pump_period); //pump for 2 seconds
        Serial.println("Turning Pump off");
        digitalWrite(POMPOUT, false);
        digitalWrite(LED, true); //turn off LED
        Serial.println("End of iteration");
        Serial.println(" ");
  }
  // If running time < 30 seconds, just print readings 
  else 
  {
    Serial.println("ONLY READ SENSOR DATA FOR FIRST 30 SECONDS"); 
    Serial.println(" ");
  }
  delay(10000); //wait 10 second before next reading
}
