#pragma once

#include "ws2812.h"
#include "color.h"

static inline void rgblite_setrgb(uint8_t _r, uint8_t _g, uint8_t _b) {
    rgb_led_t leds[RGBLED_NUM] = {{.r = _r, .g = _g, .b = _b}, {.r = _r, .g = _g, .b = _b}};
    ws2812_setleds(leds, RGBLED_NUM);
}
