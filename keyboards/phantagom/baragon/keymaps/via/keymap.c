// Copyright 2023 <dennis@kruyt.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_P1,  KC_P2, KC_P3, KC_P4,
    KC_P5,  KC_P6, KC_P7,
    KC_P8,   MO(1),   KC_P9   
  ),
  [1] = LAYOUT(
    RGB_TOG , RGB_MOD , RGB_HUI, _______,
    _______, _______, _______,
    _______, _______, _______
  ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
			if (clockwise) {
				tap_code(KC_VOLD);
			} else {
				tap_code(KC_VOLU);
			}
    return true;
}