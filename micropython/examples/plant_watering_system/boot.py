# This file is executed on every boot (including wake-boot from deepsleep)
import esp
from utils import read_config, InitialSetUp

if __name__ == "__main__":
    esp.osdebug(None)
    CONFIG = read_config("config.json")
    run = InitialSetUp(CONFIG)
    run.wifi_config()  # Connect to WIFI
    run.set_tz()  # Set timezone
