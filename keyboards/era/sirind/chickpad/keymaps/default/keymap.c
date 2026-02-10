// Copyright 2024 QMK (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
    [0] = LAYOUT(
        KC_1   , KC_2   , KC_3   , KC_4   , KC_ENT ,
        KC_LSFT, KC_VOLU, KC_VOLD, KC_UP  ,
        KC_SPC ,          KC_LEFT, KC_DOWN, KC_RGHT
    )
};
