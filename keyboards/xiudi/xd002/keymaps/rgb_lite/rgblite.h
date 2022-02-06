#pragma once

#include "ws2812.h"
#include "color.h"

static inline void rgblite_setrgb(uint8_t _r, uint8_t _g, uint8_t _b) {
    LED_TYPE leds[RGBLED_NUM] = {{.r = _r, .g = _g, .b = _b}, {.r = _r, .g = _g, .b = _b}};
    ws2812_setleds(leds, RGBLED_NUM);
}

static void rgblite_increase_hue(void) {
    static uint8_t state = 0;

    state = (state + 1) % 3;
    switch (state) {
        case 1:
            rgblite_setrgb(RGB_RED);
            break;
        case 2:
            rgblite_setrgb(RGB_BLUE);
            break;
        default:
            rgblite_setrgb(RGB_GREEN);
            break;
    }
}
