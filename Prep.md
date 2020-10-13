# Plant Tech 🌱

We're excited to have you join this course, where you'll be working with plants, Arduino boards, moisture sensors and watering systems.

The aim of Make Days is to explore and learn new things. You don't need to achieve specific goals. The structure caters for varying levels of experience; different Makers will learn different things by playing with the same tools!

# Preparing for the Make Day

Makers that are well prepared get the most out of their experience. Before you attend your Make Day, there are a couple of activities to complete.

## Step 1 - Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software)

## Step 2 - Set up your system

We will begin by installing the ESP8266 (that thingy in your box with the micro-USB port) support for the Arduino IDE:

- Open de Arduino IDE
- Go to Files (for Windows) or Arduino (for Mac) > Preferences
- Copy this: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Past it in the 'Additional Boards Managers URLs' field
- Click OK and close the preferences window
- Go to Tools > Board > Boards Manager...
- Navigate to esp8266 by esp8266 community and install the software for Arduino.

## Step 3 - Connect your ESP8266

Now it's time to plug the ESP8266 board in your computer, and see how to blink an LED (the Hello World in the electronics):

- Navigate to Tools > ESP8266 Boards (2.7.4) > NodeMCU 1.0 (ESP-12E Module)
- Select the right USB port from Tools > Port
- Clone (or download, or simply copy-paste to your Arduino IDE window) the [BlinkESP](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/BlinkESP.ino) code and run it in Arduino IDE by clicking 'Upload'.
- After compiling and uploading, the LED on your ESP8266 board should start flashing. You did it!

### Troubleshooting

If your USB port does not show up in Tools > Port, you may need [the driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for the usb-uart.

When that doesn't solve the problem, (this seems to happen when using a MacBook with an USB-C adapter) check this [forum](https://apple.stackexchange.com/questions/334311/connection-of-esp32-esp8266-not-recognized-using-macbook-pro).

If you're still stuck, let us know in the Slack Channel so we can help you get it to work!
