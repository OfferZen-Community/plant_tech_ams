import esp
import gc
import json
import machine
import network
import ntptime
import urequests
import utime
import usocket

from ubinascii import hexlify
from umqtt.simple import MQTTClient


class WiFi:
    """
    Connect to the WiFi.
    Based on the example in the micropython documentation.
    """

    def __init__(self, essid, password):
        self.essid = essid
        self.password = password

    def wifi_connect(self):
        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        if not wlan.isconnected():
            print("connecting to network '%s'..." % self.essid)
            wlan.connect(self.essid, self.password)
            # connect() appears to be async - waiting for it to complete
            while not wlan.isconnected():
                print("waiting for connection...")
                utime.sleep(5)
            print("WiFi connect successful, network config: %s" % repr(wlan.ifconfig()))
        else:
            # Note that connection info is stored in non-volatile memory. If
            # you are connected to the wrong network, do an explicity disconnect()
            # and then reconnect.
            print("WiFi already connected, network config: %s" % repr(wlan.ifconfig()))

    def wifi_disconnect(self):
        # Disconnect from the current network. You may have to
        # do this explicitly if you switch networks, as the params are stored
        # in non-volatile memory.
        wlan = network.WLAN(network.STA_IF)
        if wlan.isconnected():
            print("Disconnecting...")
            wlan.disconnect()
        else:
            print("Wifi not connected.")

    def disable_wifi_ap(self):
        # Disable the built-in access point.
        wlan = network.WLAN(network.AP_IF)
        wlan.active(False)
        print("Disabled access point, network status is %s" % wlan.status())


class InitialSetUp:
    def __init__(self, config_dict, utc_shift=2):
        self.utc_shift = utc_shift
        self.setup_wifi = WiFi(
            config_dict["wifi_config"]["ssid"], config_dict["wifi_config"]["password"]
        )

    def wifi_config(self, disableAP=False):
        if disableAP:
            self.setup_wifi.disable_wifi_ap()

        try:
            print("## Connecting to WiFi")
            self.setup_wifi.wifi_connect()
            print("## Connected to WiFi")
        except Exception:
            print("## Failed to connect to WiFi")
            utime.sleep(5)
            self.setup_wifi.wifi_disconnect()
            machine.reset()

    def set_tz(self):
        # Timezone setup
        ntptime.settime()
        rtc = machine.RTC()
        tm = utime.localtime(utime.mktime(utime.localtime()) + (self.utc_shift * 3600))
        tm = tm[0:3] + (0,) + tm[3:6] + (0,)
        rtc.datetime(tm)


class MQTTWriter:
    """Writer interface over umqtt API."""

    __variables__ = ("host", "client")
    __flag = False

    def __init__(self, host):
        self.host = host
        if self.host:
            self.client = MQTTClient(
                client_id=hexlify(machine.unique_id()),
                server=self.host
            )
            self.check_ip_up()
            self._connect()

    def check_ip_up(self):
        try:
            s = usocket.socket(usocket.AF_INET, usocket.SOCK_STREAM)
            s.settimeout(1)
            s.connect((self.host, 1883))
            print(self.host + " is UP!")
            self.__flag = True
        except Exception:
            print(self.host + "is DOWN!")
            utime.sleep(1)
        finally:
            s.close()

    def _connect(self):
        print("Connecting to %s" % (self.host))
        if self.__flag:
            self.client.connect()
            print("Connection successful")
        else:
            print("Cannot connect to host:%s" % self.host)

    def publish(self, topic="", msg="", encoder="utf-8"):
        print("Publishing message: %s on topic: %s" % (msg, topic))
        if self.__flag:
            self.client.publish(bytes(topic, encoder), bytes(msg, encoder))
            print("Published Successfully!")
        else:
            print("Failed to Publish the message, Link is not UP!")


def force_garbage_collect():
    # Not so ideal but someone has to do it
    gc.collect()
    gc.mem_free()


def current_time():
    year, month, day, hours, mins, secs, _, _ = utime.localtime()
    hours = "0" + str(hours) if hours < 10 else hours
    secs = "0" + str(secs) if secs < 10 else secs
    mins = "0" + str(mins) if mins < 10 else secs
    datetime = "%s-%s-%s %s:%s:%s" % (year, month, day, hours, mins, secs)
    return datetime


def read_config(filename):
    with open(filename) as _f:
        config = json.load(_f)
    assert isinstance(config, dict)
    return config


def enter_deep_sleep(secs):
    # For some weird reason, my Wemos D1 does not wake up from deepsleep
    """
    Ensure that pin RST & D0 are connected!
    """
    # configure RTC.ALARM0 to be able to wake the device
    rtc = machine.RTC()
    rtc.irq(trigger=rtc.ALARM0, wake=machine.DEEPSLEEP)
    # set RTC.ALARM0 to fire after Xseconds, waking the device
    sleep_timeout = secs * 1000
    rtc.alarm(rtc.ALARM0, sleep_timeout)
    print('Sleep for %d sec' % sleep_timeout)
    # put the device to sleep
    machine.deepsleep()
