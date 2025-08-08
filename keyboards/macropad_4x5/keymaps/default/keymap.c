// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7,
        KC_F4,   KC_F5, KC_F6, KC_F7
    )
};
