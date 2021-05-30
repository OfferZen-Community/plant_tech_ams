from plant_watering_system import SystemController
from utils import read_config

if __name__ == "__main__":
    filename = "config.json"
    config = read_config(filename)
    pws = SystemController(config)
    pws.run()
    # plant_watering_system.blink()