from plant_watering_system import plant_watering_system
from utils import read_config

if __name__ == "__main__":
    filename = "config.json"
    config = read_config(filename)
    plant_watering_system(config)
    plant_watering_system.run()