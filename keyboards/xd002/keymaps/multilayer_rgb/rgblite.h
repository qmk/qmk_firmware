#pragma once

#include "ws2812.h"
#include "rgblight_list.h"

static inline void rgblight_setrgb(uint8_t _r, uint8_t _g, uint8_t _b) {
    LED_TYPE leds[RGBLED_NUM] = {{.r = _r, .g = _g, .b = _b}, {.r = _r, .g = _g, .b = _b}};
    ws2812_setleds(leds, RGBLED_NUM);
}
