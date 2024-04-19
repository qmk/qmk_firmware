// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_1,   KC_2,   KC_3,   KC_4,
        KC_Q,   KC_W,   KC_E,   KC_R,
        KC_A,   KC_S,   KC_D,   KC_F,
        KC_Z,   KC_X, KC_C, KC_V,
        KC_5,   KC_6,   KC_7,   KC_8,
        KC_T,   KC_Y,   KC_U,   KC_I,
        KC_G,   KC_H,   KC_J,   KC_K,
        KC_B,   KC_N, KC_M, KC_L
    )
};
