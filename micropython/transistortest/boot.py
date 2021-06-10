# Quick Triode Model Transistor test for NodeMCU and TIP31C
from machine import Pin
import esp

if __name__ == "__main__":
    esp.osdebug(None)

    # Test diodes in forward bias
    base = Pin(16, Pin.OUT)
    collector = Pin(5, Pin.IN)
    emitter = Pin(4, Pin.IN)
    base.on()
    collector_forward = collector.value()
    emitter_forward = emitter.value()
    base.off()

    # Test diodes in reverse bias
    base = Pin(16, Pin.IN)
    collector = Pin(5, Pin.OUT)
    emitter = Pin(4, Pin.OUT)
    collector.on()
    base_reverse = base.value()
    emitter_reverse = emitter.value()
    collector.off()

    print("Both diodes should be high for the forward bias diode test (1)")
    print("The collector diode is:", collector_diode_forward)
    print("The emitter diode is:", emitter_diode_forward)

    if (collector_diode_forward and emitter_diode_forward):
        print("Forward bias diode test successful")
    else:
        print("Forward bias diode test failed - transistor is faulty")

    print("Both diodes should be low for the reverse bias diode test (0)")
  
    print("The collector diode is:", collector_diode_forward)
    print("The emitter diode is:", emitter_diode_forward)

    if (not collector_diode_reverse and not emitter_diode_reverse):
        print("Reverse bias diode test successful")
    else:
        print("Reverse bias diode test failed - transistor is faulty")

    if (collector_diode_forward and emitter_diode_forward and not collector_diode_reverse and not emitter_diode_reverse):
        print("The transistor appears to be working correctly")
    else:
        print("The transistor appears to be faulty")