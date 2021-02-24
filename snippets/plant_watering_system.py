import time

from machine import Pin

led = Pin(2, Pin.OUT)
moisture_lvl_analog = machine.ADC(0)
moisture_lvl_digital = Pin(14, Pin.IN)
pump = Pin(12, Pin.OUT)

while True:
    print(“moisture level is {}“.format(moisture_lvl_analog.read()))
    if moisture_lvl_analog.read() < 500:
        print(“Pump is Off”)
        print(“moisture_lvl_digital is {}“.format(moisture_lvl_digital.value()))
        led.off()
        pump.off()
    else:
        print(“Pump is On”)
        print(“moisture_lvl_digital is {}“.format(moisture_lvl_digital.value()))
        led.on()
        pump.on()
    time.sleep(1)
