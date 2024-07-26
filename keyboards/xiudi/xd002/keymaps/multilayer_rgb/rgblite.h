#pragma once

#include "ws2812.h"
#include "color.h"

static inline void rgblite_init(void) {
    ws2812_init();
}

static inline void rgblite_setrgb(uint8_t _r, uint8_t _g, uint8_t _b) {
    rgb_led_t leds[RGBLIGHT_LED_COUNT] = {{.r = _r, .g = _g, .b = _b}, {.r = _r, .g = _g, .b = _b}};
    ws2812_setleds(leds, RGBLIGHT_LED_COUNT);
}
