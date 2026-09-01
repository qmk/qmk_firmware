// Copyright 2024 Stephen Onnen (@onnenon)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Enable the power pin for the Xiao Seeed rp2040 onboard NeoPixel
    gpio_set_pin_output(GP11);
    gpio_write_pin_high(GP11);

    keyboard_pre_init_user();
}
