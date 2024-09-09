// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ws2812.h"

#if defined(WS2812_RGBW)
void ws2812_rgb_to_rgbw(ws2812_led_t *led) {
    // Determine lowest value in all three colors, put that into
    // the white channel and then shift all colors by that amount
    led->w = MIN(led->r, MIN(led->g, led->b));
    led->r -= led->w;
    led->g -= led->w;
    led->b -= led->w;
}
#endif
