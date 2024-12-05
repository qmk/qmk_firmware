// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ R │ O │ T │
     * ├───┼───┼───┤
     * │ C │ 0 │ N │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_2x3(
        KC_R, KC_O, KC_T,
        KC_C, KC_0, KC_N
    )
};
