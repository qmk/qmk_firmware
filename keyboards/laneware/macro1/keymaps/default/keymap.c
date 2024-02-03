// Copyright 2023 Laneware Peripherals
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* 
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K02│K03│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * ├───┼───┼───┤   │ 
 * │K30│K31│K32│   │
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * ├───┴───┼───┤   │ 
 * │K50    │K52│   │
 * └───────┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_numpad(
		KC_MUTE, KC_MPLY,     KC_BSPC, 
		KC_CALC, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, 
		KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS, 
		KC_KP_4, KC_KP_5,     KC_KP_6, 
		KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER, 
		KC_KP_0, KC_KP_DOT)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif


