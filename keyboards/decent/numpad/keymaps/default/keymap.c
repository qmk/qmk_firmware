// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *     /─────/─────/
    *    /F11  /F12  /
    *   /─────/─────/
    * ┌───┬───┬───┬───┐
    * │Num│ / │ * │ - │
    * ├───┼───┼───┼───┤
    * │ 7 │ 8 │ 9 │ + │
    * ├───┼───┼───┤   │
    * │ 4 │ 5 │ 6 │   │
    * ├───┼───┼───┼───┤
    * │ 1 │ 2 │ 3 │Ent│
    * ├───┴───┼───┤ er│
    * │ 0     │ . │   │
    * └───────┴───┴───┘
    */
    [0] = LAYOUT(
        KC_F11,  KC_F12,

        MO(1),   KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,
        KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS,
        KC_KP_4, KC_KP_5,     KC_KP_6,
        KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER,
        KC_KP_0,              KC_KP_DOT
    ),
    [1] = LAYOUT(
        S(KC_F11), S(KC_F12),
        
        _______, _______, _______, RM_VALD,
        _______, RM_HUEU, _______, RM_VALU,
        RM_SPDD, _______, RM_SPDU,
        RM_PREV, RM_HUED, RM_NEXT, QK_BOOT,
        RM_TOGG,          _______
    ),
};
