#pragma once

#include "ws2812.h"
#include "color.h"

static inline void rgblite_init(void) {
    ws2812_init();
}

static inline void rgblite_setrgb(uint8_t r, uint8_t g, uint8_t b) {
    ws2812_set_color_all(r, g, b);
    ws2812_flush();
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
