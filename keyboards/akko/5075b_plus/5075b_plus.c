// Copyright 2026 rijojohn
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

/* Power for the WS2812 chain is gated by two lines, and both are needed: with only
 * A9 asserted the first pixel lights but the rest of the chain stays unpowered and
 * therefore dark. Driven before rgb_matrix initialises. */
void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(A8);
    gpio_write_pin_high(A8);
    gpio_set_pin_output(A9);
    gpio_write_pin_high(A9);

    keyboard_pre_init_user();
}
