# Telegram with OTA Updates.

## Summary
This script will enable you to interact with your self watering plant by using a telegram bot.
You will also be able to update your code by sending new code to your arduino, using this telegram bot.

# Mandatory prerequisites
The following steps need to be done for this script to work.

## Filling the WiFi DEFINES
Set the SSID and Password of the WiFi your Arduino needs to connect to in WIFISSID and WIFIPASSWORD.
We need WiFi with internet access for this to work (obviously).

## Creating a telegram bot
Talk to the botfather (https://t.me/botfather), and create a new bot (/newbot)
It will talk you through it, and at the end, you will get a token for your bot.
This token needs to be set in the Arduino code (TELEGRAMBOTID).

## Finding your Telegram ID for admin functions
Talk to the userinfobot (https://t.me/userinfobot), and it will give you your account info.
Your Id needs to be set in the Arduino code (TELEGRAMUSERID).

Make sure to start a conversation with your bot, otherwise it won't be able to send messages to you.

## Rewiring moisture sensor (To prevent Corrosion)
(credit to https://github.com/SamLoys, copied from DeepSleepDataLogger).

This a very easy and useful.

### How?
The only thing we need to do is changing the wire that goes from `VVC` to the `3.3v` to `VVC` to `D1`. With this method, we can see the `Digital 1`pin to HIGH when we need to sensor and put it to LOW when we don't need this.

### Why?
With the default configuration, the moisture sensor is connected directly to the `3.3v` pin. There are two reasons why we don't want this. The fist is that even in deep sleep, these pins are turned `ON`. Meaning the sensor is always on and always using energy which is in this case 35 mA! By disabling the sensor completely we save energy making our system lasting even longer on the battery. You can see that the sensor is always running as the green lights are always on.

The second reason is Corrosion, if there is always running electricity through the sensor corrosion occurs, reducing the lifespan of the sensor and it is also bad for the soil. For more information this page explains it a bit better :) https://lastminuteengineers.com/soil-moisture-sensor-arduino-tutorial/

### Caution
Not every Digital pin is suitable for this, as if some digital pins are connected to `ground` the microcontroller will reboot indefinitely. The `D1` pin is tested and works.
"At least make sure all of GPIO0, GPIO2 and GPIO15 are never directly wired to either Vcc or ground." https://www.esp8266.com/viewtopic.php?p=67502

# How to send code updates using Telegram?
Manually change the code to send when someone requests /version (This is also very useful to see if your new code is actually running!)
Export your code as a binary file by going to Menu => Sketch => Export compiled binary.
It will be saved as a .bin in the same folder as your .ino files (Check preferences to see the location).
Send the .bin file to your bot, with the caption /fw_update
The bot will inform you about its progress and reboot once it is done updating.
