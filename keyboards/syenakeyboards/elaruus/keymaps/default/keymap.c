// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_1x2(
        LT(1,KC_LEFT),  LT(2,KC_RIGHT)
    ),
    [1] = LAYOUT_ortho_1x2(
        _______,          KC_UP
    ),
    [2] = LAYOUT_ortho_1x2(
        KC_DOWN,        _______
    )
};
