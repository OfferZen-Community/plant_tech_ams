# plant_watering_system



[![Python](https://img.shields.io/badge/Python-3.6%2B-red.svg)](https://www.python.org/downloads/)



Plant Watering System on ESP8266

# Installation


## Circuit Diagram

![image](assets/)

## Setup NodeMCU & Tools

Read the [docs](https://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html)

TL;DR
*   Clone the repo and,
*   Plug in the device to your computer

    **NOTE:** The installation assumes that the port name of device is `/dev/ttyUSB0` else, modify `Makefile` with port name [Hint:`$ ls /dev/tty.*`].
*   Run `make bootstrap`

    **NOTE:** This will install `esptool` and `mpfshell` for communicating with ESP chips and for serial connection with MicroPython boards, Eraze and flash the chip with firmware `esp8266-20190125-v1.10.bin` as well as upload the required files to the ESP.


## Feedback

Feel free to fork it or send me PR to improve it.

# Oh, Thanks!

By the way...
Click if you'd like to [saythanks](https://saythanks.io/to/>pbrizzolari)... :) else *Star* it.

✨🍰✨
