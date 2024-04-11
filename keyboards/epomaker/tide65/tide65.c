// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// clang-format off
void keyboard_pre_init_kb(void) {
    setPinOutput(A5);
    writePinHigh(A5);
    keyboard_pre_init_user();
}
// clang-format on



