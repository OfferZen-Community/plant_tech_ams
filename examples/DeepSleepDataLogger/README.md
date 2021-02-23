# Deepsleep data logger

## Summary
This script will enable deep sleep and turns your plant into a data logger. This means that it will significantly use less power and saves the analogue value in a google sheet.

# Mandatory prerequisites
The following steps need to be done for this script to work. 
## Creating the webhooks
To save the data into an excel sheet we need a webhook where we can send the data. The website https://ifttt.com/home is a very easy way to do this. If you are not familiar with this website the following tutorial gives a very simple and easy explanation.  https://www.youtube.com/watch?v=fRfZ0XPjT0o

For the program to work we need two webhooks created with IFTTT, one that saves the data in google sheets, and another to send a notification to your phone when the pump starts. 

# Optional prerequisites
## Enabling deep sleep
### How
To enable deep sleep an additional wire needs to be added to your esp8266 module. The wire needs to go from `DO` to the `RST` pin. if this is not done, your microcontroller will not boot up again after deep sleep. For more in-depth information, the following blog gives a great explanation https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep. 
### Why?
Why do we want this? Because we can! and also to reduce energy consumption, it goes from 20mA to 0.2 mA, wow!

### Pitfall/Trouble
This deep sleep is very cool because it now uses way less energy, however, some power banks do not like this. Why? Because "smart" power banks "think" no device is connected and shut off completely and when this happens the microcontroller does not start again, luckily cheaper power banks don't do this! So if you have troubles with a power bank going off you can try another power bank, use net power or don't use deep sleep.

## Rewiring moisture sensor (To prevent Corrosion )
This a very easy and useful
### How?
The only thing we need to do is changing the wire that goes from `VVC` to the `3.3v` to `VVC` to `D1`. With this method, we can see the `Digital 1`pin to HIGH when we need to sensor and put it to LOW when we don't need this. 
### Why?
With the default configuration, the moisture sensor is connected directly to the `3.3v` pin. There are two reasons why we don't want this. The fist is that even in deep sleep, these pins are turned `ON`. Meaning the sensor is always on and always using energy which is in this case 35 mA! By disabling the sensor completely we save energy making our system lasting even longer on the battery. You can see that the sensor is always running as the green lights are always on.

The second reason is Corrosion, if there is always running electricity through the sensor corrosion occurs, reducing the lifespan of the sensor and it is also bad for the soil. For more information this page explains it a bit better :) https://lastminuteengineers.com/soil-moisture-sensor-arduino-tutorial/
### Caution
Not every Digital pin is suitable for this, as if some digital pins are connected to `ground` the microcontroller will reboot indefinitely. The `D1` pin is tested and works. 
"At least make sure all of GPIO0, GPIO2 and GPIO15 are never directly wired to either Vcc or ground." https://www.esp8266.com/viewtopic.php?p=67502