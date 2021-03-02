/*    
    moisture_sensor_calibration.ino (v 1.0) - Sketch with helpers for resistive moisture sensor analog 
    calibration.

    Program will start in WRITE mode with range set to manufacturer's specification.

    When switching to RECORD mode you need to dip the probe into a glass of water, remove, 
    rinse and repeat as many times as you feel necessary. This will calculate the upper and 
    lower bounds of your particular probe. 
    
    These values are also updated in the map function which allows you to test them out after 
    recording is complete.

    If upper and lower bounds are accurate you should see values from 0%-5% when dipped into 
    water and 97%-100% when removed.

    Instructions:
    - Program will start in WRITE state. This state outputs changes in moisture readings to serial
      as a percentage of dryness. 
    - Dip the probe into a glass of water to measure deviation from factory defaults. If no deviation
      then a value of 100% out of water and 0%-5% in water is returned.
    - Send a 'R' or 'r' (without ') character to board via serial port to switch to RECORD state
    - This state will display and store upper and lower bounds of probe as it is dipped into water
    - When satisfied that new bounds are read (dipping the probe once or twice is sufficient) send
      a 'S' or 's' to set new bounds, display values and switch back to WRITE. These values can
      be used to define the upper and lower readings of your sensor
    - Dip probe into water once or twice to confirm readings.

    Notes:
    - Tested on:
      - Arduino Duemilanove
      - Arduino Uno R3
      - Arduino Mega 2560 R3
      - Arduino Nano v3
      - Arduino Leonardo R3
      - NodeMCU 1.0 (ESP8266)
    - ESP8266 serial behavior might prevent initial outputs from being delivered to serial even after 
      call to !Serial. Not necessarily a problem if initial readings don't appear for ESP8266. You 
      can proceed to dip the probe and see if values are updated on screen.
      
    Created by Rénaldo Meere, 24 February 2021
    Released into the public domain
*/

#include <Arduino.h>
#include "state.h"

#define SENSOR_ANALOG_PIN A0

enum state
{
  STATE_IDLE,
  STATE_RECORDING,  
  STATE_WRITE_PERCENTAGE,
};

state currentState = STATE_WRITE_PERCENTAGE;

int minReading = 0;
int maxReading = 1023;
int lastReading = 101; //Put this out of range so sensor is forced to take first reading and update

void setup()
{
  Serial.begin(115200);
  pinMode(SENSOR_ANALOG_PIN, INPUT);
  while (!Serial)  
  {
    delay(10);
  }  
}

void loop()
{
  if (Serial.available() > 0)
    readForNewState();

  if (currentState == STATE_WRITE_PERCENTAGE)
  {
    writePercentageReadings();   
  }
  else if (currentState == STATE_RECORDING)
  {
    recordReadings();     
  }

  delay(100);
}

String getStateDescription(state state)
{
  switch (state)
  {
  case STATE_RECORDING:
    return "RECORDING";
  case STATE_WRITE_PERCENTAGE:
    return "WRITING PERCENTAGES";
  default:
    return "IDLE";
  }
}

void readForNewState()
{
  char value = Serial.read();

  if ((value == 'R' || value == 'r') && currentState != STATE_RECORDING)
  {
    switchToRecording();
  }
  else if ((value == 'S' || value == 's') && currentState == STATE_RECORDING)
  {    
    Serial.println("State changed to STOP RECORDING, CALCULATING");
    printoutRangeReadings();
  }  
  else if ((value == 'W' || value == 'w') && currentState != STATE_WRITE_PERCENTAGE)
  {
    Serial.println("State changed to WRITING PERCENTAGES");
  }
}

void switchToWriting()
{
  currentState = STATE_WRITE_PERCENTAGE;  
  Serial.println("State changed to " + getStateDescription(currentState));  
}

void writePercentageReadings()
{
  int value = analogRead(SENSOR_ANALOG_PIN);

  value = map(value, minReading, maxReading, 0, 100);
  
  if (value != lastReading)
  {    
    lastReading = value;
    Serial.println((String)"Dryness (percentage): " + value);
  }
}

void switchToRecording()
{
  currentState = STATE_RECORDING;
  minReading = 1023;
  maxReading = 0;
  
  Serial.println("State changed to " + getStateDescription(currentState));
  Serial.println("Dip the probe into a glass of water and remove it. Repeat this until you are satisfied, twice should generally be enough");
}

void recordReadings()
{
  int value = analogRead(SENSOR_ANALOG_PIN);
  
  if (value < minReading)
  {
    minReading = value;
    Serial.println((String)"New lower bound: " + minReading);
  }
  else if (value > maxReading)
  {
    maxReading = value;
    Serial.println((String)"New upper bound: " + maxReading);
  }
}

void printoutRangeReadings()
{
  Serial.println("");
  Serial.println((String)"Highest reading (sensor upper range): " + maxReading);
  Serial.println((String)"Lowest reading (sensor lower range): " + minReading);
  switchToWriting();
}
