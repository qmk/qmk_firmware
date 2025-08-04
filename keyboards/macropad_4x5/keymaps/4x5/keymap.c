// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        KC_F4,   KC_F5, KC_F6, KC_BACKSPACE,
        KC_TAB,   KC_7, KC_8, KC_9,
        KC_DELETE,   KC_4, KC_5, KC_6,
        KC_LEFT_SHIFT,   KC_1, KC_2, KC_3,
        KC_LEFT_ALT,   KC_INSERT, KC_0, KC_DOT
    )
};
