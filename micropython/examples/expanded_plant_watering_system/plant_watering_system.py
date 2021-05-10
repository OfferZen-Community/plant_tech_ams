# -*- coding: utf-8 -*-

"""Main module."""
import time
from machine import Pin
from machine import ADC
import dht

from utils import force_garbage_collect


# This is where you'll want to modify 
class SystemController(object):
    # flash_btn = Pin(0, Pin.IN, Pin.PULL_UP)
    ana = ADC(0)
    digi = Pin(14, Pin.IN)
    pump = Pin(12, Pin.OUT, 0)
    env = dht.DHT22(Pin(4))

    def __init__(self, config_dict):
        self.config = config_dict

    def run(self, seconds=1):
        # This loop will continue running until we reset the board in flash mode
        # This is analagous to the loop function in the android code
        nextCheck=0
        while True:
            # This will break out of our loop if the flash button is pressed to allow us to upload new files.

            # if(not flash_btn.value()):
            #     break
            if(time.ticks_ms()>nextCheck):
                analogValue = self.ana.read()
                digitalValue = self.digi.value()
                self.env.measure()
                humidity = self.env.humidity()
                temperature = self.env.temperature()
                print("Analog raw: "+str(analogValue))
                print("Digital raw: "+str(digitalValue))
                print("Humidity: "+str(humidity))
                print("Temperature: "+str(temperature))
                if(digitalValue==0):
                    self.pump.off()
                else:
                    print("Pumping")
                    self.pump.on()

                # Set the next check tick
                nextCheck = time.ticks_ms()+(seconds*1000)

    def blink(self, seconds=1000):
        led = Pin(2, Pin.OUT)
        curr = False
        while True:
            curr = not curr
            led(curr)
            time.sleep(1000)
