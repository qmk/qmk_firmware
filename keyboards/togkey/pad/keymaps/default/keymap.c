// Copyright 2025 TogKey
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_VOLD,  KC_VOLU,
        KC_MPRV, KC_MPLY, KC_MNXT
    )
};
