// Copyright 2022 raylax (@raylax)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define NO XXXXXXX

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    BASE,
    L1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [BASE] = LAYOUT(
        LT(L1, KC_1), KC_2, KC_3
    ),
    [L1] = LAYOUT(
        NO, KC_C, KC_V
    )
};
