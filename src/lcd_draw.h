#pragma once

#include <stdint.h>

#include "image565.h"


namespace draw {

void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void image(uint16_t x, uint16_t y, const Image565 *img);
void imageTinted(uint16_t x, uint16_t y, const Image565 *img, uint16_t tint);
void imageShifted(uint16_t x, uint16_t y, const Image565 *img, uint8_t shiftHi, uint8_t shiftLo);

}
