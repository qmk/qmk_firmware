// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(A5);
    gpio_write_pin_high(A5);
    keyboard_pre_init_user();
}
