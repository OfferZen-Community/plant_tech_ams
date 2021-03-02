# Read upper and lower bounds from resistive soil sensor
Author - Rénaldo Meere.
Version - 1.0.
Date - 26 February 2021.
Released into the public domain.

## What you will need
1. Your Make kit with ESP8266 NodeMCU.
2. Soil sensor connected to 3V, G and A0 as per wiring diagram (note that digital is not used in the example).
3. A glass of water for calibration.
4. moisture_sensor_calibration.ino

## Introduction
By default, the soil sensor included in the kit is set to work with an analogue read range of 0 - 1023 indicating values of completely-wet to completely-dry. This is achieved by measuring the resistance between the two ends of the probe. 

Due to a difference in manufacturing techniques, as well as a range of environmental and equipment factors, some sensors do not achieve the minimum and maximum bounds. Generally, this does not constitute a problem, but it does need to be considered if you want to make use of the analogue readings to get incremental values of soil moisture.

It is possible in some cases to achieve these values by adjusting the potentiometer located on the sensor but on some hardware, this will not be sufficient to achieve readings between 0 and 1023.

This utility assists with identifying the upper and lower bounds that the connected sensor achieves by recording these values and reporting them back for easy reference.

It also allows you to test the readings after the range has been identified to make sure that they correspond to the correct settings.

## How to use this utility
1. Start by connecting the resistive sensor pins for 3V, G and A0.
2. Upload the sketch to your Arduino Board.
3. Open the serial monitor and make sure it is set to a baud rate of 115200.
4. Dip the moisture sensor probe in the glass of water and confirm that the values printed in serial monitor change as the probe is inserted and removed. *NB: be careful to not insert the probe too far past the portion where the metal circuit is exposed on the circuit board. Inserting it up to the point where the jumper is connected could cause a short circuit. Stop before reaching this point*
5. If you are getting readings of 100 down to 0 when doing this then you probably don’t need to calibrate your setup.
6. To start calibrating, use the serial monitor and send the character ‘R’ (without ‘) to the board. You should get a message telling you that the board has entered a RECORDING state.
7. Repeat step 4 a few times. Generally once or twice is enough.
8. Once you are satisfied that the sensor was immersed completely a few times you can use the serial monitor again and send the character ‘S’.
9. Your board will exit the RECORDING state and display the new bounds that were discovered. Write down these values because they indicate the upper and lower bounds of your particular setup.
10. The firmware will also update the variables used in the map function to reflect these new values. *NB: These values reset to original values when the board is reset. They are not retained because the starting values are flashed as part of the firmware. You need to repeat from Step 1 if you reset the board*
11. Repeat step 4 to make sure that you are able to get readings between 0%-5% and 95%- 100%.

## Reading the moisture value
The moisture value is mapped as a range between 0 and 100 and indicates how dry the sensor is. This is achieved by using the map() function built into the standard Arduino library.

For more information: https://www.arduino.cc/reference/en/language/functions/math/map/

Initially the upper bound of this range is set to 1023 and the lower bound to 0. 

Factory defaults translate to:
-	A value of 1023 would translate to a moisture reading of 100% dry.
-	A value of 0 would translate to a moisture reading of 0% dry.
-	A value of 512 would translate to a moisture reading of 50% dry.

After running the RECORD function at least once, these values are updated to reflect the upper and lower bounds of your particular sensor and the input to the map() function will be updated to reflect this. Here is an example to demonstrate how your readings *might* look once done.

-	A value of 654 would translate to a moisture reading of 100% dry.
-	A value of 124 would translate to a moisture reading of 0% dry.
-	A value of 389 would translate to a moisture reading of 50% dry.

## Notes and general observations
Tested on the following boards:
- Arduino Duemilanove
- Arduino Uno R3 with Ethernet shield
- Arduino Mega 2560 R3
- Arduino Nano v3 with Ethernet shield
- Arduino Leonardo R3
- NodeMCU 1.0 (ESP8266)

ESP8266 serial behaviour might prevent initial outputs from being delivered to serial even after the call to (!Serial). Not necessarily a problem if initial readings do not appear for ESP8266. You can proceed to dip the probe and see if values are updated on screen. This was not a problem on other Arduino boards and seems to be isolated to the way the ESP8266 serial behaviour is handled in particular.

In rare cases your sensor readings might be inverted so that 0 means it is completely wet. The map() function will still work in these instances to indicate the moisture but you'd need to consider that it displays "wetness" instead of "dryness".

## Troubleshooting
### No readings when dipping probe into liquid
Confirm wiring of the sensor:
- Sensor VCC -> ESP8266 3V
- Sensor GND -> ESP8266 G
- Sensor A0 -> ESP8266 A0

### Garbage / unreadable characters in serial monitor printout
Make sure that serial monitor baud rate is set to 115200

### Negative readings of moisture
Sensor might be using inverted configuration where completely dry could translate to 0. You can still use this utility and ignore the -
