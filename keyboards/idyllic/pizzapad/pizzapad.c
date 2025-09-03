// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Set encoder pin C low
    gpio_set_pin_output_push_pull(ENCODER_PIN_C);
    gpio_write_pin_low(ENCODER_PIN_C);

    keyboard_pre_init_user();
}
