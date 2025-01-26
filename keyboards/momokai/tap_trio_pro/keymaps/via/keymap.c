// Copyright 2023 peepeetee
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Z,   KC_X,   KC_C,
        KC_GRV,   KC_ESC,   KC_F2
    ),
};
