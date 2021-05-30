import esp
from machine import Pin
import time

led = Pin(2, Pin.OUT, 0)

if __name__ == "__main__":
    esp.osdebug(None)
    current = False
    while True:
        if current:
            led.on()
            print("LED Off")
        else:
            led.off()
            print("LED On")
        current = not current
        time.sleep(1)
