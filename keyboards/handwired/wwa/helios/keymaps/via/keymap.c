// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F13,   KC_F14,   KC_F15,   KC_F16,
        KC_F17,   KC_F18,   KC_F19,   KC_F20,
        KC_F21,   KC_F22,   KC_F23,   KC_F24
    )
};
