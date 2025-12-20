#pragma once

#include <Arduino.h>
#include <stdint.h>


typedef struct {
    uint16_t width;
    uint16_t height;
    const uint8_t *data;
} Image565;


static inline uint16_t image565_getPixel(const Image565 *img, uint16_t x, uint16_t y) {
    uint32_t offset = ((uint32_t)y * img->width + x) * 2;

    uint8_t hi = pgm_read_byte(img->data + offset);
    uint8_t lo = pgm_read_byte(img->data + offset + 1);

    return (hi << 8) | lo;
}