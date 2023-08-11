// Copyright 2023 Laneware Peripherals
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT (
		KC_MPLY, KC_MUTE,  
		KC_MNXT,  
		KC_MPRV,  KC_LEFT,    KC_RIGHT),    

	[1] = LAYOUT (
		KC_TRNS, KC_TRNS, 
		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

	[2] = LAYOUT (
		KC_TRNS, KC_TRNS, 
		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

	[3] = LAYOUT (
		KC_TRNS, KC_TRNS, 
		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [2] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};
#endif
