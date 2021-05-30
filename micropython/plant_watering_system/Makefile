######################################################################
# User configuration
######################################################################
.PHONY: erase flash reset firmware upload_all check repl bootstrap

help:
	@echo "Please use \`make <target>' where <target> is one of"
	@echo "   erase : Eraze flash on chip"
	@echo "   flash : Upload new firmware to chip"
	@echo "   reset : Hard reset chip"
	@echo "   firmware: Download latest firmware from http://www.micropython.org/download#esp8266"
	@echo "   upload: Upload latest firmware"
	@echo "   check: Compile Python code "
	@echo "   repl: Open repl on chip"
	@echo "   bootstrap: eraze, flash, and upload"

# Serial port
# Linux Debian/Ubuntu
PORT=cu.usbserial-110
SPEED=115200

# Path to programs
# Install with `sudo pip install -U mpfshell esptool`
MPFSHELL=mpfshell --open $(PORT)
ESPTOOL=esptool.py
FIRMWARE=./firmware.bin
# Get latest version from http://www.micropython.org/download#esp8266
FIRMWAREVERSION=esp8266-20190125-v1.10.bin

######################################################################
# End of user config
######################################################################
FILES=boot.py \
	config.json \
	main.py \
	plant_watering_system.py \
	utils.py

erase:
	$(ESPTOOL) --port /dev/$(PORT) erase_flash
	@sleep 3

flash: firmware
	$(ESPTOOL) --port /dev/$(PORT) --baud $(SPEED) write_flash --flash_size=detect 0 $(FIRMWARE)
	@sleep 10
	@echo 'Power cycle the device'

reset:
	$(MPFSHELL) --reset

install:
	@bash -c "if ! command -v esptool.py >/dev/null 2>&1; then pip install --user -U esptool;fi"
	@bash -c "if ! command -v mpfshell >/dev/null 2>&1; then pip install --user -U mpfshell;fi"

firmware:
	@bash -c "[ -f $(FIRMWARE) ] || wget -O ./firmware.bin http://micropython.org/resources/firmware/"$(FIRMWAREVERSION)

# Upload all
upload:
	for f in $(FILES); do \
		echo installing $$f; \
		$(MPFSHELL) -nc rm $$f > /dev/null 2>&1; \
		$(MPFSHELL) -nc put $$f; \
		echo done installing; \
	done

check:
	python3 -m py_compile *.py
	rm -rf __pycache__
	rm -f *.pyc

repl:
	$(MPFSHELL) -c repl

bootstrap: install erase flash check upload
