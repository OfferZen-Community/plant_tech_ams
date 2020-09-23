# Plant Tech 🌱

We're excited to have you join this course, where you'll be working with plants, Arduino boards, moisture sensors and watering systems.

The aim of Make Days is to explore and learn new thing. You don't need to achieve specific goals. The structure caters for varying levels of experience and different Makers will learn different things by playing with the same tools.

# Preparing for the Make Day

Makers that arrive well prepared get the most out of their experience. Before you attend your Make Day, there are a couple of activities to complete.

## Prep

Here's a list of things you'll need to prep before you can set up your biltong maker. 

- Install the [Arduino IDE](https://www.arduino.cc/en/main/software)
- Read the [Quick Start to Nodemcu (ESP8266) on Arduino IDE](https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/)

Important: if you want to use the ESP8266 WEB Server in this example you will need to downloand the following two libraries. These libraries are not available in the library manager.

### Installing the ESPAsyncWebServer library
The ESPAsyncWebServer library is not available to install in the Arduino 
Library Manager. So, you need to install it manually.

Follow the next steps to install the ESPAsyncWebServer library:

https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip

Unzip the .zip folder and you should get ESPAsyncWebServer-master folder
Rename your folder from ESPAsyncWebServer-master to ESPAsyncWebServer
Move the ESPAsyncWebServer folder to your Arduino IDE installation libraries folder

### Installing the ESPAsync TCP Library
The ESPAsyncWebServer library requires the ESPAsyncTCP library to work. Follow the next steps to install that library:

https://github.com/me-no-dev/ESPAsyncTCP/archive/master.zip

Unzip the .zip folder and you should get ESPAsyncTCP-master folder
Rename your folder from ESPAsyncTCP-master to ESPAsyncTCP
Move the ESPAsyncTCP folder to your Arduino IDE installation libraries folder
Finally, re-open your Arduino IDE

You may also need [the driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for the usb-uart

# What will be available for you on the evening

* ESP8266
* Dopunt f-f wires (x10)
* Moisture sensor
* Micro usb to usb A cable
* Watering pump
* PVC tube
* TIP31C Transistor

# How to get started

## Pinouts
ESP8266:
![ESP8266 Legend](https://i1.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-ESP-12E-chip-pinout-gpio-pin.png?ssl=1)

Mini Submersible 5V Water Pump:
![waterpump](https://potentiallabs.com/cart/image/cache/catalog/New%20Components-17/Mini%20Waterpump-800x800.png)

TIP31C Transistor
![TIP31C Transistor](https://www.componentsinfo.com/wp-content/uploads/2020/08/tip31c-pinout-equivalent.gif)

## Manuals
- [Soil Moisture Sensor Tutorial for Arduino, ESP8266 and ESP32](https://diyi0t.com/soil-moisture-sensor-tutorial-for-arduino-and-esp8266/)
- [ESP8266 smart plant irrigation system](https://iot-playground.com/blog/2-uncategorised/94-esp8266-smart-plant-irrigation-system)

## Code
If you coding isn't your strong suit, just use the code provided in the repo:
- [Moisture Sensor](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/MoistureSensor.ino)
- [Complete Watering System](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/plant_watering_system.ino)

# Further ideas


# Useful resources
- [OfferZen Make Subreddit](https://www.reddit.com/r/offerzenmake): check it out and upvote any answers you find useful. Feel free to add your own questions and comments!
- [ ] Join Make Slack, introduce yourself in #meet-and-greet, and check in with your team channel
- [ ] Learn about the how, where and why of Make Days with the [Make Manifesto](https://docs.google.com/document/d/12OtTltO-ozhGd7OzDswgLoRMLtfd3_i8_Pxw1Dx551U/edit)

*Know somebody who would enjoy this course? Tell your friends to [register here.](https://forms.gle/fk8hYZLWES6fhCCg8)

