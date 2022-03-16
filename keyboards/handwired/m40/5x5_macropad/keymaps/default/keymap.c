// Copyright 2022 Tomek (@m40-dev)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
	_BASE,
	_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_ortho_5x5(
		//┌────────┬────────┬────────┬────────┬────────┐
		   KC_ESC,   KC_1,     KC_2,    KC_3,   RESET, 
		//├────────┼────────┼────────┼────────┬────────┤
		    KC_1,    KC_2,     KC_3,    KC_4,   KC_5, 
		//├────────┼────────┼────────┼────────┼────────┤
		   	KC_1,    KC_2,     KC_3,    KC_4,   KC_5, 
		//├────────┼────────┼────────┼────────┼────────┤
		   	KC_1,    KC_2,     KC_3,    KC_4,   KC_5, 
		//├────────┼────────┼────────┼────────┼────────┤
		   	KC_1,    KC_2,     KC_3,    KC_4,   KC_5 )
		//└────────┴────────┴────────┴─────────────────┘
};
