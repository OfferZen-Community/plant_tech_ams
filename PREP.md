# Preparing for the Make Event

Makers that are well prepared get the most out of their experience. Before you attend your Make Day, there are a couple of activities to complete. Please walk through the steps below and make sure to have a working system before the actual Make session starts. It should only take about 15 minutes!

## Step 1 - Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software). Alternatively you can use [Micropython](https://github.com/OfferZen-Make/plant_tech_ams#micropython-submitted-by-michiel-erasmus) or [Eclipse](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#sloeber-a-free-open-source-eclipse-ide-submitted-by-robin-gilham)

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

Now it's time to plug the ESP8266 board in your computer, and see how to blink an LED (the Hello World in the electronics):

- Navigate to Tools > ESP8266 Boards (2.7.4) > NodeMCU 1.0 (ESP-12E Module)
- Select the right USB port from Tools > Port
- If Port is not available in Win10 (https://sparks.gogo.co.nz/ch340.html)
- Clone (or download, or simply copy-paste to your Arduino IDE window) the [BlinkESP](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/BlinkESP.ino) code and run it in Arduino IDE by clicking 'Upload'.
- After compiling and uploading, the LED on your ESP8266 board should start flashing. You did it!

## Step 4 - Test your water pump

- Strip the red and black wires of the pump.
- Plug the ESP8266 into your laptop or a cellphone charge using the MicroUSB cable.
- From your water pump press the red wire onto the 3V3 pin and black to GND pin or hook them up using the dupont wires.
- You should hear the motor of the pump spinning.

<a href="https://www.youtube.com/watch?v=0SQNkLzuTr8"> <img src="https://raw.githubusercontent.com/OfferZen-Make/plant_tech_ams/master/course_media/test_pump.png" width="300"/></a>

Alternatively
- Use a 3V battery and press the wires directly onto it.

Troubleshooting
- Ensure the wires are stripped enough.
- The lubricant can dry up. You can try heating the pump to liquefy the lubricant, or you can bash it really hard on the table which sometimes loosens it up.

### Big Sur compatibility issue:

If you're getting this issue `pyserial or esptool directories not found next to this upload.py tool` when uploading your sketch on Big Sur, [click here](https://forum.arduino.cc/index.php?topic=702144.0#msg4793318) for the workaround.

<img src="https://media.giphy.com/media/3ohryhNgUwwZyxgktq/giphy.gif" alt="seven" width="300"/>

### Troubleshooting

All project troubleshooting is here https://github.com/OfferZen-Make/plant_tech_ams/wiki

## Step 5 - Take a photo of your setup and share it!

Please help us spread the word about Make events so that we can grow the community and keep helping devs learn new tech 🚀 💦 🌱.

### Share photo on Twitter

1. Take a photo of your set up
2. Click here to [📸  -> Share on Twitter](https://twitter.com/intent/tweet?url=&text=I'm%20setup%20and%20ready%20to%20go%20for%20my%20%23offerzenmake%20event%20with%20%40offerzen!) with a message

### && / || Share photo on LinkedIn

If you don't have Twitter you can share it on LinkedIn. Steps:
* Copy this message: `I'm setup and ready to go for my #offerzenmake event with @offerzen! `.
* Upload a photo of your setup and the message above to [LinkedIn](https://www.linkedin.com/).

### Fabulous example

Here's a fabulous example from @hendrikdelarey

[<img src="https://i.imgur.com/seoUZT8.png"/>](https://twitter.com/hendrikdelarey/status/1336696671556825091?s=20)

### If you don't do social media...

And if you abhor all social media and don't do any of that then please share it on the #project-arduino-plant channel in Slack 😂 Thank you, it really helps to keep the lights on 💡. See you soon <3

## Step 6 - Chart a course for self-watering plant mastery

Read through the [Plant Tech readme](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md) including [project extensions](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#project-extensions), [community contributions](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#community-contributions) and [useful resources](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/README.md#useful-resources) to get an idea for where you want to take your self-watering plant project on the evening of the event.

Please edit or add to the docs as you go!
