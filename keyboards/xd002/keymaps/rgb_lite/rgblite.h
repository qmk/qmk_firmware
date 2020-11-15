#pragma once

#include "ws2812.h"
#include "rgblight_list.h"

static inline void rgblight_setrgb(uint8_t _r, uint8_t _g, uint8_t _b) {
    LED_TYPE leds[RGBLED_NUM] = {{.r = _r, .g = _g, .b = _b}, {.r = _r, .g = _g, .b = _b}};
    ws2812_setleds(leds, RGBLED_NUM);
}

static void rgblight_increase_hue(void) {
    static uint8_t state = 0;

    state = (state + 1) % 3;
    switch (state) {
        case 1:
            rgblight_setrgb_red();
            break;
        case 2:
            rgblight_setrgb_blue();
            break;
        default:
            rgblight_setrgb_green();
            break;
    }
}
