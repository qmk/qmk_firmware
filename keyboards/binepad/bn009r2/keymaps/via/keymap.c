// Copyright 2023 Binepad
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * ├───┼───┼───┤
     * │ G │ H │ I │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x3(
        KC_7,   KC_8,   KC_9,
        KC_4,   KC_5,   KC_6,
        KC_1,   KC_2,   KC_3
    ),

    [1] = LAYOUT_ortho_3x3(
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO
    ),

    [2] = LAYOUT_ortho_3x3(
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO
    ),

    [3] = LAYOUT_ortho_3x3(
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO
    )
};
