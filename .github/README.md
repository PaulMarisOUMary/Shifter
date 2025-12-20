# Shifter

Gear shift indicator display using a round IPS LCD.

## Hardware

- [Surenoo 0.96" 240×198 SPI IPS Round LCD](https://fr.aliexpress.com/item/1005006258472043.html) - [ST7789H2 controller](https://www.lcdwiki.com/res/MSP0962_MSP0963/ST7789H2.pdf)
- [Nano SuperMini](https://fr.aliexpress.com/item/1005006583241212.html) - ATmega328P with CH340 USB

## Prerequisites

**Arduino CLI**  
Download and extract to `tools/arduino-cli.exe`:  
https://github.com/arduino/arduino-cli/releases/latest

**Python** (for image conversion)  
Version 3.8 or later

## Setup

1. Install Arduino AVR core:
   ```
   make core-install
   ```

2. Create Python virtual environment and install dependencies:
   ```
   make venv
   ```

## Building & Uploading

**Compile only:**
```
make compile
```

**Compile and upload** (default port: COM6):
```
make upload
```

**Upload to different port:**
```
make upload PORT=COM3
```

## Image Conversion

Convert PNG images to RGB565 format for the display:

```
make images
```

This processes `img/*_gear.png` files and generates [src/images.h](src/images.h).

## Project Structure

- `src/` - Arduino sketch files
  - `src.ino` - Main program
  - `lcd_driver.*` - ST7789H2 display driver
  - `lcd_draw.*` - Graphics primitives
  - `gear_ui.*` - Gear indicator UI
- `tools/` - Python image conversion utilities
- `build/` - Compiled artifacts (generated)

## Other Commands

```
make info          # List connected boards
make monitor       # Serial monitor
make clean         # Remove build files
```
