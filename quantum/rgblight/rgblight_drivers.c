// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgblight_drivers.h"

#if defined(RGBLIGHT_WS2812)
#    include "ws2812.h"

const rgblight_driver_t rgblight_driver = {
    .init    = ws2812_init,
    .setleds = ws2812_setleds,
};

#elif defined(RGBLIGHT_APA102)
#    include "apa102.h"

// Temporary shim
static void apa102_setleds(rgb_led_t *ledarray, uint16_t number_of_leds) {
    for (uint16_t i = 0; i < number_of_leds; i++) {
        apa102_set_color(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
    }
    apa102_flush();
}

const rgblight_driver_t rgblight_driver = {
    .init    = apa102_init,
    .setleds = apa102_setleds,
};

#endif
