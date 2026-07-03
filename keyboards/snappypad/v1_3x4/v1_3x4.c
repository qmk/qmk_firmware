// Copyright 2025 Snappy Key <snappykey@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

void keyboard_post_init_kb(void) {
    gpio_set_pin_output(F7);
    gpio_set_pin_output(B2);
    gpio_set_pin_output(B5);

    keyboard_post_init_user();
}
