#include <avr/pgmspace.h>

#include "lcd_draw.h"
#include "lcd_driver.h"


namespace draw {

void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    if (x >= lcd::WIDTH || y >= lcd::HEIGHT) return;
    if (x + w > lcd::WIDTH) w = lcd::WIDTH - x;
    if (y + h > lcd::HEIGHT) h = lcd::HEIGHT - y;

    lcd::beginWrite();
    lcd::setAddressWindow(x, y, x + w - 1, y + h - 1);

    for (uint16_t row = 0; row < h; ++row) {
        for (uint16_t col = 0; col < w; ++col) {
            lcd::writeData16(color);
        }
    }

    lcd::endWrite();
}

void image(uint16_t x, uint16_t y, const Image565 *img) {
    if (!img || x >= lcd::WIDTH || y >= lcd::HEIGHT) return;

    const uint16_t w = img->width;
    const uint16_t h = img->height;
    const uint8_t *data = img->data;

    lcd::beginWrite();
    lcd::setAddressWindow(x, y, x + w - 1, y + h - 1);

    const uint32_t totalBytes = (uint32_t)w * h * 2;
    for (uint32_t i = 0; i < totalBytes; ++i) {
        lcd::writeData(pgm_read_byte(data + i));
    }

    lcd::endWrite();
}

void imageTinted(uint16_t x, uint16_t y, const Image565 *img, uint16_t tint) {
    if (!img || x >= lcd::WIDTH || y >= lcd::HEIGHT) return;

    const uint16_t w = img->width;
    const uint16_t h = img->height;
    const uint8_t *data = img->data;

    const uint8_t tintHi = static_cast<uint8_t>(tint >> 8);
    const uint8_t tintLo = static_cast<uint8_t>(tint & 0xFF);

    lcd::beginWrite();
    lcd::setAddressWindow(x, y, x + w - 1, y + h - 1);

    const uint32_t totalPixels = (uint32_t)w * h;
    for (uint32_t i = 0; i < totalPixels; ++i) {
        uint8_t hi = pgm_read_byte(data + i * 2);
        uint8_t lo = pgm_read_byte(data + i * 2 + 1);
        lcd::writeData(hi & tintHi);
        lcd::writeData(lo & tintLo);
    }

    lcd::endWrite();
}

void imageShifted(uint16_t x, uint16_t y, const Image565 *img, uint8_t shiftHi, uint8_t shiftLo) {
    if (!img || x >= lcd::WIDTH || y >= lcd::HEIGHT) return;

    const uint16_t w = img->width;
    const uint16_t h = img->height;
    const uint8_t *data = img->data;

    lcd::beginWrite();
    lcd::setAddressWindow(x, y, x + w - 1, y + h - 1);

    const uint32_t totalPixels = (uint32_t)w * h;
    for (uint32_t i = 0; i < totalPixels; ++i) {
        uint8_t hi = pgm_read_byte(data + i * 2);
        uint8_t lo = pgm_read_byte(data + i * 2 + 1);
        lcd::writeData(hi >> shiftHi);
        lcd::writeData(lo >> shiftLo);
    }

    lcd::endWrite();
}

}
