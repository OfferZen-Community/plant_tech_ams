/*
  Blink an ESP8266 NodeMCU board
  Turns flashes an LED for one second delay.
  
  This program needs no circuit. It will use a built-in LED
  
  by Eng. Alaa Al Nassan
 */


# define LED D4 // Use built-in LED which connected to D4 pin or GPIO 2

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the LED as an output
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED, HIGH);  // Turn the LED off because the LED is active low
  Serial.println("ON");
  delay(1000);            // Wait a second
  digitalWrite(LED, LOW);   // Turn the LED on because the LED is active low
  Serial.println("OFF");
  delay(1000);              // Wait a second
}




