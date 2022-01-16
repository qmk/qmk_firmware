// Copyright 2022 KnoblesseOblige (@KnoblesseOblige)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
                 KC_UP,
        KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [1] = LAYOUT(
                _______,
        _______, _______, _______
    ),
    [2] = LAYOUT(
                _______,
        _______, _______, _______
    ),
    [3] = LAYOUT(
                _______,
        _______, _______, _______
    ),
};
