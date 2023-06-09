// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_post_init_kb(void) {
    // If the keyboard is master, turn on power to the split half, and to underglow LEDs
    if (is_keyboard_master()) {
        setPinOutput(A15);
        writePinHigh(A15);
    };
    keyboard_post_init_user();
}