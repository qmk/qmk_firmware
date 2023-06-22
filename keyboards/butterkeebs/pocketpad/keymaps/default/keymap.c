// ButterKeebs <butterkeebs@github>
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_NUM_LOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, 
		KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, 
		KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ENTER, 
		KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT, 
		KC_F, KC_KP_0)
};