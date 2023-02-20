// Copyright 2022 Synth and Keys (@Synth-and-Keys)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * -------------
     * | 1 | 2 | 3 |
     * -------------
     * | 4 | 5 | 6 |
     * -----------------
     * | 7 | 8 | 9 | 0 |
     * -----------------

     */
    [0] = LAYOUT(
        KC_P1,   KC_P2,   KC_P3,
        KC_P4,   KC_P5,   KC_P6,
        KC_P7,   KC_P8,   KC_P9,   KC_P0
    )
};