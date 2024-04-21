// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void matrix_init_kb(void) {
    gpio_set_pin_output(B2);
    gpio_write_pin_high(B2);
    matrix_init_user();
}
