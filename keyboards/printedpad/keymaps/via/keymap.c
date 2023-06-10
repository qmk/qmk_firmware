// Copyright 2023 Noah Beidelman (@noahbei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │Tog│ 
     * ├───┼───┬───┐ 
     * │ 1 │ 2 │ 3 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 7 │ 8 │ 9 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x3(
        LT(0, KC_NO),
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    ),

    [1] = LAYOUT_ortho_4x3(
        LT(0, KC_NO),
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    ),

    [2] = LAYOUT_ortho_4x3(
        LT(0, KC_NO),
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    ),

    [3] = LAYOUT_ortho_4x3(
        LT(0, KC_NO),
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    )
};