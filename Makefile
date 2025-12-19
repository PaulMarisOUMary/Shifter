ARDUINO_CLI ?= tools/arduino-cli.exe

# Board: Nano (ATmega328P) OLD bootloader
FQBN ?= arduino:avr:nano:cpu=atmega328old

# Board port: COM3, COM5, ...
PORT ?= COM6

# Sketch folder (Arduino requires the main .ino file to match the folder name)
SKETCH ?= src

BUILD_DIR ?= build

# Serial monitor baud (if using serial)
MONITOR_BAUD ?= 115200

ifeq ($(OS),Windows_NT)
CLEAN_CMD = powershell -NoProfile -Command "if (Test-Path '$(BUILD_DIR)') { Remove-Item -Recurse -Force '$(BUILD_DIR)' }"
else
CLEAN_CMD = rm -rf $(BUILD_DIR)
endif

.PHONY: all help info core-install compile upload monitor clean

all: compile

help:
	@echo Targets:
	@echo   make info          - show detected boards/ports
	@echo   make core-install  - install Arduino AVR core (arduino:avr)
	@echo   make compile       - build into $(BUILD_DIR)
	@echo   make upload        - upload to PORT=$(PORT)
	@echo   make monitor       - serial monitor on PORT
	@echo   make clean         - remove build output
	@echo 
	@echo Variables (override e.g. make upload PORT=COM5):
	@echo   ARDUINO_CLI=$(ARDUINO_CLI)
	@echo   FQBN=$(FQBN)
	@echo   PORT=$(PORT)
	@echo   SKETCH=$(SKETCH)
	@echo   BUILD_DIR=$(BUILD_DIR)

info:
	$(ARDUINO_CLI) version
	$(ARDUINO_CLI) board list

core-install:
	$(ARDUINO_CLI) core update-index
	$(ARDUINO_CLI) core install arduino:avr

compile:
	$(ARDUINO_CLI) compile --fqbn $(FQBN) --warnings all --build-path $(BUILD_DIR) $(SKETCH)

upload: compile
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(FQBN) --input-dir $(BUILD_DIR) $(SKETCH)

monitor:
	$(ARDUINO_CLI) monitor -p $(PORT) -c baudrate=$(MONITOR_BAUD)

clean:
	$(CLEAN_CMD)

