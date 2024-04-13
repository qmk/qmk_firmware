// Copyright 2024 zvecr <git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Workaround for reversible pcb/mcu
    gpio_set_pin_input_high(C13);
    gpio_set_pin_input_high(C15);
    gpio_set_pin_output_open_drain(B7);
    gpio_set_pin_output_open_drain(A0);
    gpio_set_pin_output_open_drain(A1);

    keyboard_pre_init_user();
}
