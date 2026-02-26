// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#define LED_ENABLE_PIN A5
void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(LED_ENABLE_PIN);
    gpio_write_pin_high(LED_ENABLE_PIN);
    keyboard_pre_init_user();
}