import esp
import time
from machine import Pin
from machine import ADC

ana = ADC(0)
digi = Pin(14, Pin.IN)

if __name__ == "__main__":
    esp.osdebug(None)
    current = False
    while True:
        nextCheck=0
        while True:
            if(time.ticks_ms()>nextCheck):
                analogValue = self.ana.read()
                digitalValue = self.digi.value()
                print("Analog raw: "+str(analogValue))
                print("Digital raw: "+str(digitalValue))

                # Set the next check tick
                nextCheck = time.ticks_ms()+(seconds*1000)
