// Copyright 2026 Kento Lauzon (@keotl)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_NUM,  KC_P7,            KC_P9,
        KC_P1,   KC_P4,   KC_P8,
                 KC_P2,            KC_P6,
        KC_P0,            KC_P5,   KC_P3
    )
};
