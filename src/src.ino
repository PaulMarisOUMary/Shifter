#include "lcd_driver.h"
#include "lcd_draw.h"
#include "gear_ui.h"


constexpr uint16_t COLOR_ACTIVE   = 0xEF7D;
constexpr uint16_t COLOR_INACTIVE = 0xA4F4;

void setup() {
    lcd::initController();
    lcd::clear(0x0000);

    gear::drawLogo();

    lcd::fadeIn();

    delay(500);
}

void loop() {
    for (uint8_t i = 0; i < static_cast<uint8_t>(gear::Position::COUNT); ++i) {
        gear::Position active = static_cast<gear::Position>(i);
        gear::drawAllGears(active, COLOR_ACTIVE, COLOR_INACTIVE);
        delay(500);
    }

    for (uint8_t i = 0; i < static_cast<uint8_t>(gear::Position::COUNT); ++i) {
        gear::drawGear(static_cast<gear::Position>(i), COLOR_ACTIVE);
    }
    delay(500);
}