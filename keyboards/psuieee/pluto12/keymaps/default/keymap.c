// Copyright 2021-22 Will McGLoughlin (wymcg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_PGUP,   KC_MUTE,   KC_VOLD,   KC_VOLU,
        KC_PGDN,   KC_MPLY,   KC_MPRV,   KC_MNXT,
        KC_NO,     KC_HOME,   KC_END,    OSL(_FN)
    ),
    [_FN] = LAYOUT(
        KC_F1,     KC_F2,     KC_F3,     KC_F4,
        KC_F5,     KC_F6,     KC_F7,     KC_F8,
        KC_F9,     KC_F10,    KC_F11,    KC_F12
    )
};
