// Copyright 2022 Makoto Kurauchi (@MakotoKurauchi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ws2812.h"
#include "color.h"

static inline void rgblite_setrgb(RGB rgb) {
    LED_TYPE leds[RGBLED_NUM] = {{.r = rgb.r, .g = rgb.g, .b = rgb.b}};
    ws2812_setleds(leds, RGBLED_NUM);
}

static void rgblite_increase_hue(void) {
    static uint8_t state = 0;

    HSV hsv = { 255, 255, 255 };
    hsv.h = state;
    state = (state + 8) % 256;

    rgblite_setrgb(hsv_to_rgb(hsv));

}
