#include <SPI.h>

#include "lcd_driver.h"


namespace lcd {


static inline void setDataMode(bool isData) {
    digitalWrite(PIN_DC, isData ? HIGH : LOW);
}

void initPins() {
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_DC, OUTPUT);
    pinMode(PIN_RESET, OUTPUT);

    pinMode(PIN_BACKLIGHT, OUTPUT);

    digitalWrite(PIN_CS, HIGH);
    digitalWrite(PIN_DC, HIGH);
    digitalWrite(PIN_RESET, HIGH);
    digitalWrite(PIN_BACKLIGHT, LOW);
}

void initSPI() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);  // 4 MHz
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
}

void beginWrite() {
    digitalWrite(PIN_CS, LOW);
}

void endWrite() {
    digitalWrite(PIN_CS, HIGH);
}

void writeCommand(uint8_t cmd) {
    setDataMode(false);
    SPI.transfer(cmd);
}

void writeData(uint8_t data) {
    setDataMode(true);
    SPI.transfer(data);
}

void writeData16(uint16_t value) {
    setDataMode(true);
    SPI.transfer(static_cast<uint8_t>(value >> 8));
    SPI.transfer(static_cast<uint8_t>(value & 0xFF));
}

void setAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    writeCommand(CMD_CASET);
    writeData(static_cast<uint8_t>(x0 >> 8));
    writeData(static_cast<uint8_t>(x0 & 0xFF));
    writeData(static_cast<uint8_t>(x1 >> 8));
    writeData(static_cast<uint8_t>(x1 & 0xFF));

    writeCommand(CMD_RASET);
    writeData(static_cast<uint8_t>(y0 >> 8));
    writeData(static_cast<uint8_t>(y0 & 0xFF));
    writeData(static_cast<uint8_t>(y1 >> 8));
    writeData(static_cast<uint8_t>(y1 & 0xFF));

    writeCommand(CMD_RAMWR);
}

void clear(uint16_t color) {
    beginWrite();
    setAddressWindow(0, 0, WIDTH - 1, HEIGHT - 1);

    for (uint16_t y = 0; y < HEIGHT; ++y) {
        for (uint16_t x = 0; x < WIDTH; ++x) {
            writeData16(color);
        }
    }

    endWrite();
}

void initController() {
    initPins();
    initSPI();

    // Hardware reset
    digitalWrite(PIN_RESET, HIGH);
    delay(5);
    digitalWrite(PIN_RESET, LOW);
    delay(5);
    digitalWrite(PIN_RESET, HIGH);
    delay(5);

    beginWrite();

    // ST7789H2 initialization
    writeCommand(CMD_MADCTL);
    writeData(0x00);

    writeCommand(CMD_COLMOD);
    writeData(0x05);

    writeCommand(CMD_PORCTRL);
    writeData(0x0C);
    writeData(0x0C);
    writeData(0x00);
    writeData(0x33);
    writeData(0x33);

    writeCommand(CMD_GCTRL);
    writeData(0x35);

    writeCommand(CMD_VCOMS);
    writeData(0x17);

    writeCommand(CMD_LCMCTRL);
    writeData(0x2C);

    writeCommand(CMD_VDVVRHEN);
    writeData(0x01);

    writeCommand(CMD_VRHS);
    writeData(0x12);

    writeCommand(CMD_VDVS);
    writeData(0x20);

    writeCommand(CMD_FRCTRL2);
    writeData(0x0F);

    writeCommand(CMD_PWCTRL1);
    writeData(0xA4);
    writeData(0xA1);

    writeCommand(CMD_PVGAMCTRL);
    writeData(0xD0);
    writeData(0x04);
    writeData(0x0D);
    writeData(0x11);
    writeData(0x13);
    writeData(0x2B);
    writeData(0x3F);
    writeData(0x54);
    writeData(0x4C);
    writeData(0x18);
    writeData(0x0D);
    writeData(0x0B);
    writeData(0x1F);
    writeData(0x23);

    writeCommand(CMD_NVGAMCTRL);
    writeData(0xD0);
    writeData(0x04);
    writeData(0x0C);
    writeData(0x11);
    writeData(0x13);
    writeData(0x2C);
    writeData(0x3F);
    writeData(0x44);
    writeData(0x51);
    writeData(0x2F);
    writeData(0x1F);
    writeData(0x1F);
    writeData(0x20);
    writeData(0x23);

    writeCommand(CMD_INVON);

    writeCommand(CMD_SLPOUT);
    endWrite();
    delay(120);
    beginWrite();

    writeCommand(CMD_DISPON);

    endWrite();
}

void setBrightness(uint8_t brightness) {
    analogWrite(PIN_BACKLIGHT, brightness);
}

void fadeIn(uint8_t target, uint8_t step, uint8_t delayMs) {
    for (int b = 0; b <= target; b += step) {
        setBrightness(b);
        delay(delayMs);
    }
    setBrightness(target);
}

void fadeOut(uint8_t step, uint8_t delayMs) {
    for (int b = 255; b >= 0; b -= step) {
        setBrightness(b);
        delay(delayMs);
    }
    setBrightness(0);
}

}
