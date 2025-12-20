#pragma once

#include <stdint.h>


namespace gear {

constexpr uint8_t BOLD_LINE = 4;
constexpr uint8_t DIGIT_WIDTH = 24;
constexpr uint8_t DIGIT_HEIGHT = 28;
constexpr uint8_t BIG_WIDTH = 28;
constexpr uint8_t BIG_HEIGHT = 37;

enum class Position : uint8_t {
    GEAR_1 = 0,
    GEAR_2,
    GEAR_3,
    GEAR_4,
    GEAR_5,
    GEAR_R,
    COUNT
};

void drawGear1(uint16_t color);
void drawGear2(uint16_t color);
void drawGear3(uint16_t color);
void drawGear4(uint16_t color);
void drawGear5(uint16_t color);
void drawGearR(uint16_t color);

void drawGear(Position pos, uint16_t color);
void drawAllGears(Position active, uint16_t activeColor, uint16_t inactiveColor);
void drawLogo();

}
