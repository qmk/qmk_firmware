// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgblight_drivers.h"

#if defined(RGBLIGHT_WS2812)
#    include "ws2812.h"

const rgblight_driver_t rgblight_driver = {
    .init          = ws2812_init,
    .set_color     = ws2812_set_color,
    .set_color_all = ws2812_set_color_all,
    .flush         = ws2812_flush,
};

#elif defined(RGBLIGHT_APA102)
#    include "apa102.h"

const rgblight_driver_t rgblight_driver = {
    .init          = apa102_init,
    .set_color     = apa102_set_color,
    .set_color_all = apa102_set_color_all,
    .flush         = apa102_flush,
};

#endif
