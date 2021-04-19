# -*- coding: utf-8 -*-

"""Main module."""
import machine
import time

from utils import current_time, force_garbage_collect


# This is where you'll want to modify 
class MoistureSensor(object):
    flash_btn = Pin(0, Pin.IN, Pin.PULL_UP)
    ana = machine.ADC(0)
    digi = Pin(14, Pin.IN)
    pump = Pin(12, Pin.OUT)

    def __init__(self, config_dict):
        self.config = config_dict
        pump(0)

    def run(self, seconds=1000):
        # This loop will continue running until we reset the board in flash mode
        # This is analagous to the loop function in the android code
        while True:
            # This will break out of our loop if the flash button is pressed to allow us to upload new files.

            if(!flash_btn.value()):
                break
            nextCheck=0
            if(time.ticks_ms()>nextCheck):
                analogValue = ana.read()
                digitalValue = digi.value()
                print("Analog raw: "+analogValue)
                print("Digital raw: "+digitalValue)

                if(digital==0):
                    pump.off()
                else:
                    print("Pumping")
                    pump.on()

                # Set the next check tick
                nextCheck = time.ticks_ms()+interval