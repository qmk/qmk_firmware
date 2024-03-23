// Copyright 2023 Laneware Peripherals
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT (
		KC_MPLY, KC_MUTE,  
		KC_MNXT,  
		KC_MPRV,  KC_LEFT,    KC_RIGHT)    
};

