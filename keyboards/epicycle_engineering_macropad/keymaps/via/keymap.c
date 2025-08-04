// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┤
     * │ 5 │ 6 │ 7 │ 8 │
     * ├───┼───┼───┼───┤
     * │ 9 │10 │11 │12 │
     * ├───┼───┼───┼───┤
     * │13 │14 │15 │16 │
     * ├───┼───┼───┼───┤
     * │17 │18 │19 │20 │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4,
        KC_5, KC_6, KC_7, KC_8,
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L
    )
};
