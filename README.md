# Plant Tech

Keen to join a Make Session? Go to: https://www.offerzen.com/nl/make.

Our code of conduct is a work in progress, available [here](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/code_of_conduct.md).

## **🌱 Table of Contents 🌱**
- [Preparing for the event](#preparing-for-the-event)
- [At the event](#at-the-event)
- [After the event](#after-the-event)
  - [NB! Giving feedback](#nb-giving-feedback)
- [Project extensions](#project-extensions)
- [Community Contributions](#community-project-repos)
- [Useful resources](#useful-resources)
- [Troubleshooting](#troubleshooting)

## The purpose of Make

Welcome to the community, we're excited to have you join us!

- The Make event is all about making cool things and meeting even cooler people.
- It serves as an onboarding into the OfferZen Make Community.
- It should help you get started on your journey of becoming a Maker or,
- if you are already an advanced Maker, it puts you in contact with other devs that you can help along their journeys.
- You can read a bit more in-depth into our philosophy here: [Make Manifesto](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/make_manifesto.md).

<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/image%20(15).png?raw=true" width="400">

## Preparing for the event
You'll be working with plants, Arduino boards, moisture sensors and watering systems. The aim of Make Days is to explore and learn new things - you should be challenging yourself and leaning on the community for support.

**👉 Before the event, complete the [Make Preparation Manual](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/PREP.md) to get your LED blinking and ensure you are setup for the event.**

*Please see [Troubleshooting](#troubleshooting) if you run into issues.*

For the event you will need to ensure you have:
* Tall glass or container with water to test the sensor and water pump
* Laptop/PC with USB-A port or adaptor
* Optional: small pair of pliers for crimping wire connectors

## At the event

### What will be available for you on the evening

<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/0614b0bfd892185ca7d357898836be4f137b23a5/Fritzing/ResistiveMoistureSensorCurrrent.png" alt="complete" width="900"/>

**In the diagram**
1. ESP8266 module - [how it works](https://lastminuteengineers.com/esp8266-nodemcu-arduino-tutorial/)
2. Dupont f-f wires (x10)
3. Moisture sensor
4. Watering pump
5. TIP31C Transistor

**Additionally**
* Micro usb to usb A cable
* PVC tube + cable tie
* Connector

### Part 1 - Set up your plant 🌱

#### 🇳🇱 Netherlands Teams

Add 300 ml water to the bag with pressed soil, forming ~1 liter of compost. Make a few small (1cm deep) holes in the soil and place the basil seeds in them, covering with a bit of loose soil.

Pro tip: drill some holes in the bottom of your pot to drain water coming in otherwise the roots might rot.

#### 🇿🇦 South African Teams
- Fill your pot most of the way with soil
- Sprinkle your seeds on top
- Cover with ±1 cm soil

### Part 2 - Moisture Sensor 💦

Connect the moisture sensor with the LM393 chip that comes in the same pack. The sensor has both an analog (0 for wet and 1023 for dry) and a digital (LOW for wet and HIGH for dry) output. Check the pinout for the sensor above and see where it would connect to the ESP8266 board (tip: it has an analog, digital, GND, and needs a voltage).

<img src="https://www.circuitstoday.com/arduino-soil-moisture-sensor/pin-out" alt="moisture" width="500"/>

Connect the ESP8266 with your PC and start up the Arduino IDE. Sometimes the ESP8266 does not show in your IDE. If so, look for the right USB-port (Tools > Port).

<img src="https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png?ssl=1" alt="ESP8266" width="400"/>

Try writing a little programme to print the sensor's moisture values (analog is more interesting here as it gives you a value from a wetness-range). If coding isn't your strong suit, you can use the code provided in this repo for the [Moisture Sensor](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/arduino/MoistureSensor/MoistureSensor.ino).

Upload your code to your system, wait untill the upload is done - the terminal should read: "Leaving... Hard resetting via RTS pin..." - and open the monitor (Tools > Serial Monitor) to see your printed values. Make sure that the Baud rate in the program and your serial monitor window are the same. If you used the code from the repo above, select the 115200 BAUD option for upload speed, otherwise your readings are not printed.

Put your sensor (only the two large exposed pads) in the compost of your plant, or simply put it in a glass of water, to do some readings!

Side mission! If you want to calibrate your moisture sensor, check out [Renaldo Meere's moisture sensor calibration utility](https://github.com/OfferZen-Make/plant_tech_ams/tree/master/arduino/utilities).

### Part 3 - Mini Water Pump ⛽️

The pump is water submersible, sucks in water from the hole on the opposite end of the wires, and pumps it through the little outlet. In order to switch the pump on and off, it needs to be connected to the ESP8266 with the TIP31C Transistor. The two wires of the pump go in one side, the other side takes your Dupont wires.

🇳🇱 Netherlands Community: use the connector - white block with four inlets - to do so. By lifting the plastic clip (see below) off one side of the Dupont wire, exposing the metal, you can put it in the other side of the connector.

🇿🇦 South African Community: break the silver metal crimps off the tab they come on, strip the pump wires and crimp them onto the pump wires.

<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/Dupont F2F to F2M.png" alt="moisture" width="500"/>

<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/Submersible%20Pump%20Pinout.png?raw=true" alt="pump" width="300"/> <img src="https://www.componentsinfo.com/wp-content/uploads/2020/08/tip31c-pinout-equivalent.gif" alt="tip31c" width="300"/> 

The pump has a GND output to be connected to the ESP8266 and receives power from the emitter pin of the transistor. The transistor gets its power through its collector pin from the ESP8266's 3V3 pin. Finally, connect the base to the D6 pin to be able to control the pump.

Write some code (or check the code from the [complete watering system](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/arduino/plant_watering_system/plant_watering_system.ino) in this repo) to get the pump up and running. Before uploading the code, make sure to submerse the pump in your tall glass/container filled with water, as you do not want to overheat its motor - and please watch out for water spills ;)

Your self-watering plant is set up! You can now simply plug it directly into the mains using a usb adaptor / cellphone charger with a 5v output and it will keep your plant watered.

*Additional learning: [Watch - "What's the point of the three wires on the transistor, relays and pulse width modulation?"](https://www.youtube.com/watch?v=sf9B6eeQTUE&ab_channel=OfferZen)*

### Part 4 - Time to play! 🥳

Now that the basics of your system are up and running, it's time to play around a bit! You can put your moisture sensor in your plant and attach the PVC tubing to the water pump (potentially use the cable tie to prevent leaking) with one end, and lay the other end in the plant.

See what analog value would be a good threshhold of dryness. Implement this in your code to start activating your pump as soon as this threshold is reached. Also try to implement some delays in your code to stop the pump after a few seconds, as it takes some time for the soil to get moist and the sensor to pick this up.

If you are confident that your very own automated watering system is fully working, you can check out the repos below for some inspiration on how to communicate with your system via your phone :)

- [Project extensions](#project-extensions)
- [Community Contributions](#community-project-repos)

<img src="https://media.giphy.com/media/uuxcAmIzAbKlvz4kZS/giphy.gif" alt="unbox" width="300"/>

### NB! Giving back

#### Giving feedback
After the event we only ask one further thing: please help us keep these going and growing by giving us feedback and inviting friends using the forms below 🙏
- [🇳🇱 Netherlands](https://forms.gle/NZ6FT3DuhXuW6MuG9)
- [🇿🇦 South Africa Feedback](https://docs.google.com/forms/d/e/1FAIpQLSc-JSOmKebYERO_tBQ18r8Ns89_u6GeP27yr6w9Vfl6dzV8sw/viewform)

🎁 We want to give you the gift of giving! please refer people that you think would love to attend one of our next sessions and get the Make @ Home Box delivered to their door. You can do so via the same form! 🎁 

#### Contributing to this repo

These are the steps to contribute to a project:

1. Fork the main project 👉 https://github.com/OfferZen-Make/plant_tech_ams
2. Edit the forked version. Example: https://github.com/benblaine/plant_tech_ams
3. Create a “Pull Request” from your fork back into the main project. Example: https://github.com/OfferZen-Make/plant_tech_ams/pull/38


## Project extensions

You can find extensions for the project here.

### Connect to the WiFi
Connect your ESP8266 with [your Wi-Fi](https://www.instructables.com/IoT-ESP8266-Series-1-Connect-to-WIFI-Router/)

### Build a chatbot
Let your system update you, and feed it commands, via text/slack/whatsapp with the [MessageBird API](https://github.com/mariuspot/plant_tech_ams/blob/master/webcontrol.ino)

Send messages on [slack or telegram](http://blog.danishjoshi.com/2019/11/06/sending-messages-to-a-slack-or-telegram-channel-using-esp8266/).

Telling your plant to water itself - by speech! [Blogpost + code](https://codeburst.io/home-automation-using-google-assistant-dialogflow-firebase-esp8266-wemos-part-1-800c4dc15ad9)

### Set up a web server

Example
https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/

Important: if you want to use the ESP8266 WEB Server in this example you will need to downloand the following two libraries. These libraries are not available in the library manager.

#### Installing the ESPAsyncWebServer library
The ESPAsyncWebServer library is not available to install in the Arduino IDE Library Manager. So, you need to install it manually.

Follow the next steps to install the ESPAsyncWebServer library:

https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip

Unzip the .zip folder and you should get ESPAsyncWebServer-master folder
Rename your folder from ESPAsyncWebServer-master to ESPAsyncWebServer
Move the ESPAsyncWebServer folder to your Arduino IDE installation libraries folder

#### Installing the ESPAsync TCP Library
The ESPAsyncWebServer library requires the ESPAsyncTCP library to work. Follow the next steps to install that library:

https://github.com/me-no-dev/ESPAsyncTCP/archive/master.zip

Unzip the .zip folder and you should get ESPAsyncTCP-master folder
Rename your folder from ESPAsyncTCP-master to ESPAsyncTCP
Move the ESPAsyncTCP folder to your Arduino IDE installation libraries folder
Finally, re-open your Arduino IDE

### RGB LED
Extend your project with an [RGB LED](https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/) to indicate moisture levels with colors.

## Community Project Repos

You can find code and projects and advice submitted by the community here. Please submit your code for inclusion :)

| Repo      | Description | Author |
| ----------- | ----------- | ----------- |
|[Mobile app to monitor moisture](https://github.com/sid-zip/moniter-moisture-level)|Connecting ESP device with the [Blynk](https://blynk.io/) mobile application to remotely retrieve sensor values in real-time.|[@sid-zip](https://github.com/sid-zip)|
|[Prometheus exporter](http://linkode.org/#piYml2vuWQLjiHCk0b4k05)|Connect to your WiFi and have a small webserver running there. Here is my prometheus exporter.|[@gilgamezh](https://github.com/gilgamezh/)|
|[deep sleep data logger](./examples/DeepSleepDataLogger/README.md)| This script will enable deep sleep and turns your plant into a data logger. This means that it will significantly use less power and saves the analogue value in a google sheet.|by [SamLoys](https://github.com/SamLoysa)|
|[Add multiple sensors and pumps to your make kit](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/expansions/multiple_sensors_and_pumps_by_AnriGoosen.md)|The circuit works by converting the output from 3 digital output pins to binary through the 3-8 converter and using that to switch on each sensor or pump one by one. Readings are taken from the sensors one at a time through the analog pin. The NAND gate is used to determine if the sensors or the pumps must be switched on. In theory, this can be expanded to connect up to 24 sensors and pumps to one ESP8266 NodeMCU board|by [GoosenA](https://github.com/GoosenA)|
|[OfferZenSelfWateringPlant](https://github.com/TLCoetzer/OfferZenSelfWateringPlant)|basic implimentation from the event evening. It reads the sensor values, then if greater than 400 it turns the pump on for 2 seconds, then off again for 10 seconds to give the water chance to absorb. It then reads again. If the water is reading is <= 400 then it just blinks the light on for 2 seconds and the off for 2 seconds before taking another reading. It just keeps looping like this forever.|by [TLCoetzer](https://github.com/TLCoetzer)|
|[Automatic pid water portion control](https://github.com/ikilledmypc/plantwaterer)|This project uses 2 humidity levels one for the night/morning and one for the afternoon/midday. You can set your timezone-offset and humidity levels in the web interface. I'm in the process of testing it on a live plant though so I won't take any blame for drowned plants. It does have a watchdog timer for safety.|by @ikilledmypc.|
|[Playing withb Arduino setup](https://github.com/ronaldf2000/basihetplantje)|First attempt playing with the arduino enviroment working with embedded c++ |by @ronaldf2000.|
|[OfferZen Plantfeeder](https://github.com/rvt/offerzen-plantfeeder)|Has a web interface for MQTT configuration as well as WIFI configuration. |by @ries.|
|[Self watering plant](https://github.com/cokceken/Self-watering-plant)|Code for Connecting to local wifi, Creating a web server, Managing MQTT connection, Managing sensors.|by @semih çokçeken|
|[Self watering plant using MicroPython](https://github.com/mmphego/uPython-Plant-Irrigation-System)| MicroPython based plant irrigation system running on an esp8266 with Slack and Ubidots support. | by @mmphego|
|[Self-watering plant code](https://github.com/roaldnefs/basil)|checkout the GitHub actions workflow if you wish to test if your Arduino code actually compiles before pushing it to your plant 🌱|@Roald Nefs|
|[JSON MQTT WIFI](https://github.com/rvdende/offerzenSmartPlant) | Simple realtime mqtt + json controller so you can remotely control and monitor the smartplant device. | by @rvdende|
|[Plantspy](https://github.com/ahoydave/plantspy) | Quick and dirty python web app to record and chart smartplant moisture and pump state over time | by @ahoydave |
|[Teach your plant to Tweet!](https://github.com/JacksonIsaac/basil-van-bunnik) | Introduce your lovely plant to the cute blue little bird! | by <a href="https://github.com/JacksonIsaac">@JacksonIsaac</a> |
|[Self Watering Plant](https://github.com/hirebarend/self-watering-plant) | Self Watering Plant with StatsD Integration | by <a href="https://github.com/hirebarend">@hirebarend</a> |

## Useful resources

### Sloeber: a free, open source, Eclipse IDE submitted by Robin Gilham

- Proper IDE with code completion, refactoring, syntax highlighting
- GitHub integration

[Download the product, unpack and play!](https://eclipse.baeyens.it/)

### Micropython submitted by Michiel Erasmus

Micropython = Python 3.4. No need to recompile your code. Run your code by pressing F5 (in Thonny) to run. Runs on ESP8266, ESP32-platforms. Has a filesystem so you can copy files to it from Mac/Win/Linux. Interfaces with a huuuuuuge number of sensors. CircuitPython is a fork of Micropython. Go check out Micropython. Lotsa tutorials online available, otherwise let me know if/how I can help (@MIchiel Erasmus on OfferZen Community Slack). Use https://thonny.org as editor.

@lee penrose was kind enough to submit his Python code for his self watering plant project so you can check it out to [here](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/snippets/plant_watering_system.py) - try write your own!


### 3D printed tools

#### Enclosure Mod by @Pieter Linde

Pieter Linde modified an existing plant enclosure with "OfferZen" :) You can access the printer file [here](https://www.tinkercad.com/things/bFTDSzWcusm-fabulous-rottis/edit?sharecode=lSyWL2UxdobV3gDx9X6cHZBx-7pwOPdmfentWH5Z9hE).

[<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/pieter_linde_3d_design_plant_enclosure.png?raw=true" alt="3dprintedencls" width="300"/>](https://www.tinkercad.com/things/bFTDSzWcusm-fabulous-rottis/edit?sharecode=lSyWL2UxdobV3gDx9X6cHZBx-7pwOPdmfentWH5Z9hE)
[<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/pieter_linde_3d_printed_enclosure.png?raw=true" alt="3dprintedencls" width="300"/>](https://www.tinkercad.com/things/bFTDSzWcusm-fabulous-rottis/edit?sharecode=lSyWL2UxdobV3gDx9X6cHZBx-7pwOPdmfentWH5Z9hE)

#### Water distributor by Ries

<a href="https://github.com/rvt/offerzen-plantfeeder/tree/master/box"><img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/water_distributor_by_ries.png?raw=true" width="300"> <img src="https://github.com/rvt/offerzen-plantfeeder/raw/master/box/box.jpg" width="300"></a>

You can find instructions on building this [here](https://github.com/rvt/offerzen-plantfeeder/tree/master/box).

#### Water distributor by Morne Lotze

[STL File](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/pot%20water%20ring.stl)

<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/water_distributor_by_morne_lotze.gif?raw=true" width="300">

#### Other enclosures

[<img src="https://cdn.thingiverse.com/assets/d4/de/02/49/e8/featured_preview_Planter.jpg" alt="3dprintedencls" width="300"/>](https://www.thingiverse.com/thing:4699025)
[<img src="https://cdn.thingiverse.com/assets/38/d4/28/c7/98/featured_preview_Frame_1-min_1.jpg" alt="3dprintedencls" width="300"/>](https://www.thingiverse.com/thing:4699025)

### Other things to do with Arduino

- [17 Cool Arduino Projects for DIY Enthusiasts](https://itsfoss.com/cool-arduino-projects/)
- [ESP8266 mini projects that you can use to enhance your self watering planter](https://lastminuteengineers.com/electronics/esp8266-projects/)
- [ ] [Arduino IDE for Visual Studio (Visual Micro) - Visual Studio Marketplace](https://marketplace.visualstudio.com/items?itemName=VisualMicro.ArduinoIDEforVisualStudio)
- [ ] [Node-RED](https://nodered.org/) - Node-RED is a programming tool for wiring together hardware devices, APIs and online services in new and interesting ways.
- [ ] [Flash code to other devices](https://github.com/espressif/esptool)

### Additional equipment

To shop for equipment see suppliers lists in your country:
- [South Africa](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/south_africa_equipment_suppliers.md)
- [Netherlands](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/netherlands_equipment_suppliers.md)


Here's a list of equipment that has come up as ideas for extending the project further.

| Item      | Description |
| ----------- | ----------- |
| [I2C Soil Moisture Sensor](https://www.whiteboxes.ch/shop/i2c-soil-moisture-sensor/)      | add description...       |
| [Capacitive analog moisture sensor](https://s.click.aliexpress.com/e/_Ao5xVH)      | No metal parts touching the water so no corrosion problems causing inaccuracy in the long run       |
| [Linear Voltage Regulator](https://za.rs-online.com/web/p/linear-voltage-regulators/2988508/?cm_mmc=ZA-PLA-DS3A-_-google-_-PLA_ZA_EN_Semiconductors_Whoop-_-(ZA:Whoop!)+Linear+Voltage+Regulators-_-2988508&matchtype=&pla-302356913516&gclid=CjwKCAiAo5qABhBdEiwAOtGmbg7tuEvVQIAG1wTDop1IJoNiwtXcKgqFSBNvbamjBCqnsQrGesIdEBoCXyoQAvD_BwE&gclsrc=aw.ds)      | add description...       |
|[JOY-IT DPS 5005 DPS](https://www.reichelt.com/nl/de/dps-labornetzgeraet-0-50-v-0-5-a-joy-it-dps-5005-p239863.html?r=1)|This programmable module for controlling voltage with a constant voltage and constant current.|
|[Adafruit STEMMA Soil Sensor - I2C Capacitive Moisture Sensor](https://www.adafruit.com/product/4026)|Alternative moisture sensor, multiple can be connected if using ESP2866.|
|[ELEGOO Elektronische Fun Kit](https://www.amazon.nl/ELEGOO-Elektronische-Condensator-Potentiometer-Elektronica/dp/B0855QCZ17/ref=pd_sbs_2?pd_rd_w=atFmt&pf_rd_p=12014d1e-55f2-42ac-9c37-83c84018946d&pf_rd_r=KZCBGMV7AQW7666A8QA1&pd_rd_r=cf540411-506d-4944-98dc-96d1e29668a4&pd_rd_wg=NMPIm&pd_rd_i=B0855QCZ17&psc=1)|An electronics starter kit for exploring further.|
|[Raspberry Pi 4B – Ultimate starter kit](https://www.freva.com/product/raspberry-pi-4b-ultimate-starter-kit-4gb/)|Starter kit for expanding further.|
|[AZDelivery 16 in 1 Kit](https://www.amazon.nl/dp/B071GV6L41/?coliid=IU1O5OOOZJRKR&colid=LCA4LPMQ3AWU&psc=1&ref_=lv_ov_lig_dp_it)| Expanded sensors kit|


## Troubleshooting


### USB port not showing in Tools > Port
- If your USB port does not show up in Tools > Port, you may need the driver.
  - If your board has a square chip next to the USB port then use [this driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for the usb-uart. (CP2102 Chipset)
  - If your board has a rectangular chip next to the USB port then use [this driver](https://sparks.gogo.co.nz/ch340.html) for the usb-uart. (CH340 Chipset)
  - When that doesn't solve the problem, (this seems to happen when using a MacBook with an USB-C adapter) check this [forum](https://apple.stackexchange.com/questions/334311/connection-of-esp32-esp8266-not-recognized-using-macbook-pro).
  - If you're still stuck, let us know in the Slack Channel so we can help you get it to work!

### "Fatal Error Failed to connect"
If you see a `Fatal Error Failed to connect to ESP8266: Timed out waiting for packet header` (this might not happen on the first time but in subsequent uploads): disconnect the external board and upload again, connecting the wires after this.

If this doesn't work you may need to reset your board following these steps.

#### Booting into program mode
1. Ensure serial monitor is closed.
2. While uploading your script, reset board in flash mode by holding down FLASH button, pressing RST button and releasing FLASH.
3. Hit upload and accept that it will fail the first time.
4. Hit upload again and it works.

<img src="https://github.com/OfferZen-Make/plant_tech_ams/blob/master/course_media/esp_reset_and_flash_buttons.jpg?raw=true" width=200></img>

### Board keeps switching on and off

Most laptop USB ports can only supply limited current, generally 500mA (USB-3 is 2.5A) - so when the pump is connected and drawing power it overloads the circuitry and trips the power.

Fixes.

- Use USB hub with external power
- Use a USB power supply
- Power the pump separately

### Struggling to connect to Wifi

The Arduino's Wifi antenna is very small and not very strong, so you might need to move it closer to the Wifi.

You can use [this program](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/examples/WiFi/list_wifi.ino) to find SSID's and check signal strength.

### Mac users unable to get your Hello World up and running

Solution submitted by Alex Siega

1. Under Tools > Board, make sure to select "Generic ESP8266 Module." Mine defaults to "Arduino Uno" without actively selecting the right board.
2. Install the drivers from the OfferZen Prep page. Make sure to give the drivers the correct permissions in the Security & Privacy area in System Preferences; it's at the end of the "General" tab.
3. In Tools > Port, select /dev/cu.usbserial-1420 at the port. (No mention of "right" USB port, but hey, it works! :smile:)
4. Last step -- when you go to upload blinkESP.ino, you may get a 'D4' was not declared in this scope error. Change D4 to 2 , making the first line # define LED 2

This results in a blue light flashing every second, which I believe is the "hello world" described in the prep document!

Paolo Brizzolari > @Alex Siega it’s cool that you got it working. Just a couple of points:

Using the generic 8266 doesn’t guarantee that all the pins will have the right numbers so I’d advise choosing the NodeMCU board once you’ve added the json url to the boards manager
The alias D4 that disappeared was because of the above. For each board there is an import happening in the background
If you check the esp8266 libraries you can go into variants/nodemcu/pins_arduino.h [and see the following](https://github.com/OfferZen-Make/plant_tech_ams/blob/master/snippets/pins_arduino.h).

### Mac OSX: Big Sur upload errors

If you get the following error while trying to upload a sketch to your board:

```
pyserial or esptool directories not found next to this upload.py tool.
```

Then try the steps below:

1. Open Users/?????/Library/Arduino15/packages/esp8266/hardware/esp8266/2.7.4/tools/pyserial/serial/tools/list_ports_osx.py
2. Comment out lines 29 and 30 and append these lines:
```
iokit = ctypes.cdll.LoadLibrary('/System/Library/Frameworks/IOKit.framework/IOKit')
cf = ctypes.cdll.LoadLibrary('/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation')
```

If the error is still occurring.
1. Edit ~/Library/Arduino15/packages/esp8266/hardware/esp8266/2.7.4/tools/esptool/esptool.py
2. Find the block of code below and comment it out by adding # to the start of each line:
```
#try:
#    import serial.tools.list_ports as list_ports
#except ImportError:
#    print("The installed version (%s) of pyserial appears to be too old for esptool.py (Python interpreter %s). "
#          "Check the README for installation instructions." % (sys.VERSION, sys.executable))
#    raise
```

### Windows: USB Driver issues

**Problem**
Can’t seem to find any that work for me. The ones recommended on the guide don’t help and the “port” option stays grayed out in the arduino ide.

**Solution - Adam Hillier**
I had the same issue. I installed the driver from here: https://sparks.gogo.co.nz/ch340.html. It worked for me.

### My pump isn't working

- Strip some of the provided wires and press them directly onto a 3v+ battery. We've had instances where people didn't the strip wires enough.
- You might need to hit it quite hard on the table - sometimes the lubricant dries up so it gets stuck.
- If you're using the transistor then try switching the wires around - if it's connected the wrong way around it won't work. The metal part must be flat on your desk and facing away from you on the desk and it will match the diagram.
