// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define LED_INDICATOR_PIN B2

void matrix_init_kb(void) {
    gpio_set_pin_output(LED_INDICATOR_PIN);
    gpio_write_pin_high(LED_INDICATOR_PIN);
    matrix_init_user();
}
