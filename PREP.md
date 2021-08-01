# Preparing for the Make Event

Makers that are well prepared get the most out of their experience. Before you attend your Make Day, there are a couple of activities to complete. Please walk through the steps below and make sure to have a working system before the actual Make session starts. It should only take about 15 minutes!

## Step 1 - Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software). Alternatively you can use [Micropython](https://github.com/OfferZen-Make/plant_tech_ams#micropython-submitted-by-michiel-erasmus) or [Eclipse](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#sloeber-a-free-open-source-eclipse-ide-submitted-by-robin-gilham)

For advanced users, you can use `arduino-cli`, you can set it up following [these instructions](prep-arduino-cli.md).

For interested users, you can also use `micropython`, you can set it up following [these instructions](prep-micropython.md).

## Step 2 - Set up your system

We will begin by installing the ESP8266 (that thingy in your box with the micro-USB port) support for the Arduino IDE:

- Open the Arduino IDE
- Go to Files (for Windows) or Arduino (for Mac) > Preferences
- Copy this: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Paste it in the 'Additional Boards Managers URLs' field
- Click OK and close the preferences window
- Go to Tools > Board > Boards Manager...
- Navigate to esp8266 by esp8266 community and install the software for Arduino.

## Step 3 - Connect your ESP8266

Now it's time to plug the ESP8266 board into your computer, and see how to blink an LED (the Hello World in the electronics):


- Remove the ESP8266 from it's packet.
- Navigate to Tools > ESP8266 Boards (2.7.4) > NodeMCU 1.0 (ESP-12E Module)
- Select the right USB port from Tools > Port
- If Port is not available in Win10 (https://sparks.gogo.co.nz/ch340.html) or any other errors, check [Troubleshooting](https://github.com/OfferZen-Make/plant_tech_ams#troubleshooting)
- Clone (or download, or simply copy-paste to your Arduino IDE window) the [BlinkESP](/arduino/BlinkESP/BlinkESP.ino) code and run it in Arduino IDE by clicking 'Upload'.
- After compiling and uploading, the LED on your ESP8266 board should start flashing. You did it!

Troubleshooting:
- [Mac Big Sur upload issues](https://github.com/OfferZen-Make/plant_tech_ams#mac-osx-big-sur-upload-errors)

## Step 4 - Test your water pump

- Strip the red and black wires of the pump.
- Plug the ESP8266 into your laptop or a cellphone charge using the MicroUSB cable.
- From your water pump press the red wire onto the 3V3 pin and black to GND pin or hook them up using the dupont wires.
- You should hear the motor of the pump spinning.

<a href="https://www.youtube.com/watch?v=0SQNkLzuTr8"> <img src="https://raw.githubusercontent.com/OfferZen-Make/plant_tech_ams/master/course_media/test_pump.png" width="300"/></a>

Alternatively
- Use a 3V battery and press the wires directly onto it.

Troubleshooting:
- [My pump isn't working](https://github.com/OfferZen-Make/plant_tech_ams#my-pump-isnt-working)

## Step 5 - Help us grow the community by sharing a pic 🌱🙏

Please help us spread the word about Make events so that we can grow the community and keep helping devs learn new tech 🚀 💦 🌱.

1. Use the phrase ` #OfferZenSwag with @offerzen.`
2. Share a photo or story on: [Twitter](https://twitter.com/search?q=%23OfferZenMake&src=typeahead_click&f=live), [LinkedIn](https://www.linkedin.com/feed/hashtag/offerzenmake/), [Instagram](https://www.instagram.com/offerzen/?hl=en) or [Facebook](https://www.facebook.com/hashtag/offerzenmake)

See you online soon <3

Here's a fabulous example from @hendrikdelarey

[<img src="https://i.imgur.com/seoUZT8.png"/>](https://twitter.com/hendrikdelarey/status/1336696671556825091?s=20)

## Step 6 - Chart a course for self-watering plant mastery

Read through the [Plant Tech readme](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md) including [project extensions](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#project-extensions), [community contributions](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#community-contributions) and [useful resources](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#useful-resources) to get an idea for where you want to take your self-watering plant project on the evening of the event.

Please edit or add to the docs as you go!
