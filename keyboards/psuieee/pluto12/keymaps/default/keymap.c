// Copyright %(YEAR)s %(YOUR_NAME)s (@%(USER_NAME)s)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4,
        KC_F5, KC_F6, KC_F7, KC_F8,
        KC_F9, KC_F10, KC_F11, LT(_FN, KC_F12)
    ),
    [_FN] = LAYOUT(
        KC_7, KC_8, KC_9, KC_0,
        KC_4, KC_5, KC_6, KC_0,
        KC_1, KC_2, KC_3, KC_TRNS
    )
};
