# Preparing for the Make Event

Makers that are well prepared get the most out of their experience. Before you attend your Make Day, there are a couple of activities to complete. Please walk through the steps below and make sure to have a working system before the actual Make session starts. It should only take about 15 minutes!

## Step 1 - Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software). Alternatively you can use [Micropython](https://github.com/OfferZen-Make/plant_tech_ams#micropython-submitted-by-michiel-erasmus)

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
- Clone (or download, or simply copy-paste to your Arduino IDE window) the [BlinkESP](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/BlinkESP.ino) code and run it in Arduino IDE by clicking 'Upload'.
- After compiling and uploading, the LED on your ESP8266 board should start flashing. You did it!

<img src="https://media.giphy.com/media/3ohryhNgUwwZyxgktq/giphy.gif" alt="seven" width="300"/>

### Troubleshooting

All project troubleshooting is here https://github.com/OfferZen-Make/plant_tech_ams/wiki

## Step 4 - Take a photo of your setup and share it!

Confirm you are ready by sharing your setup on Twitter using the [#offerzenmake](https://twitter.com/search?q=%23offerzenmake&src=typed_query) hashtag.

Here's a fabulous example from @hendrikdelarey

<img src="https://i.imgur.com/seoUZT8.png"/>

If you don't have Twitter you can share it on LinkedIn using the [#offerzenmake](https://www.linkedin.com/search/results/all/?keywords=%23offerzenmake&origin=GLOBAL_SEARCH_HEADER) hashtag...

And if you abore all social medias and don't do any of that then please share it on the #project-arduino-plant channel in Slack 😂
