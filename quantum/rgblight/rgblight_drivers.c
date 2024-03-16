// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgblight_drivers.h"

#if defined(RGBLIGHT_WS2812)
#    include "ws2812.h"

const rgblight_driver_t rgblight_driver = {
    .setleds = ws2812_setleds,
};

#elif defined(RGBLIGHT_APA102)
#    include "apa102.h"

const rgblight_driver_t rgblight_driver = {
    .setleds = apa102_setleds,
};

#endif
