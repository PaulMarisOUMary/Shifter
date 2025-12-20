#pragma once

#include <Arduino.h>
#include <stdint.h>


namespace lcd {

// Pin configuration for ST7789H2 on the Nano board
constexpr uint8_t PIN_LED       = A0;
constexpr uint8_t PIN_CS        = A2;
constexpr uint8_t PIN_DC        = A3;
constexpr uint8_t PIN_RESET     = A4;
constexpr uint8_t PIN_BACKLIGHT = 6;

// IPS Module dimensions
constexpr uint16_t WIDTH  = 240;
constexpr uint16_t HEIGHT = 198;

// ST7789 Commands
constexpr uint8_t CMD_MADCTL    = 0x36;
constexpr uint8_t CMD_COLMOD    = 0x3A;
constexpr uint8_t CMD_PORCTRL   = 0xB2;
constexpr uint8_t CMD_GCTRL     = 0xB7;
constexpr uint8_t CMD_VCOMS     = 0xBB;
constexpr uint8_t CMD_LCMCTRL   = 0xC0;
constexpr uint8_t CMD_VDVVRHEN  = 0xC2;
constexpr uint8_t CMD_VRHS      = 0xC3;
constexpr uint8_t CMD_VDVS      = 0xC4;
constexpr uint8_t CMD_FRCTRL2   = 0xC6;
constexpr uint8_t CMD_PWCTRL1   = 0xD0;
constexpr uint8_t CMD_PVGAMCTRL = 0xE0;
constexpr uint8_t CMD_NVGAMCTRL = 0xE1;
constexpr uint8_t CMD_INVON     = 0x21;
constexpr uint8_t CMD_SLPOUT    = 0x11;
constexpr uint8_t CMD_DISPON    = 0x29;
constexpr uint8_t CMD_CASET     = 0x2A;
constexpr uint8_t CMD_RASET     = 0x2B;
constexpr uint8_t CMD_RAMWR     = 0x2C;

void initPins();
void initSPI();
void initController();

void beginWrite();
void endWrite();

void writeCommand(uint8_t cmd);
void writeData(uint8_t data);
void writeData16(uint16_t value);

void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void clear(uint16_t color);

void setBrightness(uint8_t brightness);
void fadeIn(uint8_t target = 255, uint8_t step = 5, uint8_t delayMs = 10);
void fadeOut(uint8_t step = 5, uint8_t delayMs = 10);
}
