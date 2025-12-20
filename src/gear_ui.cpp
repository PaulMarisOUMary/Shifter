#include "gear_ui.h"
#include "lcd_draw.h"
#include "image565.h"

#define IMAGE565_IMAGES_IMPLEMENTATION
#include "images.h"


namespace gear {

void drawGear1(uint16_t color) {
    draw::fillRect(40, 79, BOLD_LINE, BIG_HEIGHT, color);  // |
    draw::fillRect(40, 116, 28, BOLD_LINE, color);         // -
    draw::imageTinted(30, 47, &image_1_gear, color);
}

void drawGear2(uint16_t color) {
    draw::fillRect(40, 120, BOLD_LINE, BIG_HEIGHT, color); // |
    draw::fillRect(40, 116, 28, BOLD_LINE, color);         // -
    draw::imageTinted(30, 161, &image_2_gear, color);
}

void drawGear3(uint16_t color) {
    draw::fillRect(118, 62, BOLD_LINE, 19, color);         // |
    draw::imageTinted(108, 30, &image_3_gear, color);
}

void drawGear4(uint16_t color) {
    draw::fillRect(118, 138, BOLD_LINE, 19, color);        // |
    draw::imageTinted(108, 162, &image_4_gear, color);
}

void drawGear5(uint16_t color) {
    draw::fillRect(172, 116, 28, BOLD_LINE, color);        // -
    draw::fillRect(196, 79, BOLD_LINE, BIG_HEIGHT, color); // |
    draw::imageTinted(186, 48, &image_5_gear, color);
}

void drawGearR(uint16_t color) {
    draw::fillRect(196, 120, BOLD_LINE, BIG_HEIGHT, color); // |
    draw::fillRect(172, 116, BIG_WIDTH, BOLD_LINE, color);  // -
    draw::imageTinted(186, 162, &image_R_gear, color);
}

void drawGear(Position pos, uint16_t color) {
    switch (pos) {
        case Position::GEAR_1: drawGear1(color); break;
        case Position::GEAR_2: drawGear2(color); break;
        case Position::GEAR_3: drawGear3(color); break;
        case Position::GEAR_4: drawGear4(color); break;
        case Position::GEAR_5: drawGear5(color); break;
        case Position::GEAR_R: drawGearR(color); break;
        default: break;
    }
}

void drawAllGears(Position active, uint16_t activeColor, uint16_t inactiveColor) {
    for (uint8_t i = 0; i < static_cast<uint8_t>(Position::COUNT); ++i) {
        drawGear(static_cast<Position>(i), inactiveColor);
    }
    drawGear(active, activeColor);
}

void drawLogo() {
    draw::image(86, 89, &image_logo_gear);
}

}
