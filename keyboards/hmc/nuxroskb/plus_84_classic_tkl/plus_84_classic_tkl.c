// Copyright 2026 HMC Studio
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "ws2812.h"

void keyboard_pre_init_kb(void) {
    // Keep the first WS2812 DIN low before the RGB Matrix driver starts.
    gpio_set_pin_output(WS2812_DI_PIN);
    gpio_write_pin_low(WS2812_DI_PIN);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Clear any color latched while the MCU was resetting before honoring EEPROM state.
    ws2812_set_color_all(0, 0, 0);
    ws2812_flush();

    keyboard_post_init_user();
}
