// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_MPLY,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_NO,	KC_MSEL,	KC_NO
    )
};

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
		if(clockwise){
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		} 
    } 
	return true;
};

#endif