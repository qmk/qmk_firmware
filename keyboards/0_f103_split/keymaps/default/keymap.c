// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐  ┌───┬───┬───┬───┐
     * │ A │ B │ C │ D │--│ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┤  ├───┼───┼───┼───┤
     * │ E │ F │ G │ H │  │ 5 │ 6 │ 7 │ 8 │
     * ├───┼───┼───┼───┤  ├───┼───┼───┼───┤
     * │ I │ J │ K │ L │  │ 9 │ 0 │ + │ - │
     * ├───┼───┼───┼───┤  ├───┼───┼───┼───┤
     * │ M │ N │ O │ P │  │ . │ : │ / │ \ |
     * └───┴───┴───┴───┘  └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_A,       KC_B,           KC_C,       KC_D,   
        KC_E,       KC_F,           KC_G,       KC_H,   
        KC_I,       KC_J,           KC_K,       KC_L,   
        KC_M,       KC_N,           KC_O,       KC_P, 
        KC_1,       KC_2,           KC_3,       KC_4,
        KC_5,       KC_6,           KC_7,       KC_8,
        KC_9,       KC_0,           KC_PLUS,    KC_MINUS,
        KC_DOT,     KC_COLON,       KC_SLASH,   KC_BACKSLASH    
    )
};
