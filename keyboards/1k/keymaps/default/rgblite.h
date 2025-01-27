// Copyright 2022 Makoto Kurauchi (@MakotoKurauchi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ws2812.h"
#include "color.h"

static inline void rgblite_init(void) {
    ws2812_init();
}

static inline void rgblite_setrgb(rgb_t rgb) {
    ws2812_set_color_all(rgb.r, rgb.g, rgb.b);
    ws2812_flush();
}

static void rgblite_increase_hue(void) {
    static uint8_t state = 0;

    hsv_t hsv = { 255, 255, 255 };
    hsv.h = state;
    state = (state + 8) % 256;

    rgblite_setrgb(hsv_to_rgb(hsv));

}
