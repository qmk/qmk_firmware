// Copyright 2022 Jimmy Lye (@satorusaka)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┬───┬───┬───┬────┐
     * │ F3 │ 9 │ 6 │ 3 │ fn │
     * ├────┼───┼───┼───┼────┤
     * │ F2 │ 8 │ 5 │ 2 │ .  │
     * ├────┼───┼───┼───┼────┤
     * │ F1 │ 7 │ 4 │ 1 │ O  │
     * └────┴───┴───┴───┴────┘
     */
    [0] = LAYOUT_default(
        KC_F3,   KC_KP_9,   KC_KP_6,   KC_KP_3,   LT(1, KC_KP_ENTER),
        KC_F2,   KC_KP_8,   KC_KP_5,   KC_KP_2,   KC_KP_DOT,
        KC_F1,   KC_KP_7,   KC_KP_4,   KC_KP_1,   KC_KP_0
    ),
    [1] = LAYOUT_default(
        RM_TOGG,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        RM_NEXT,RM_HUEU,RM_SATU,RM_VALU,RM_SPDU,
        RM_PREV,RM_HUED,RM_SATD,RM_VALD,RM_SPDD
    )
};
