// Copyright 2025 Enoch Chau <enoch965@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LIGHT,
    _EMPTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT(
		LT(1, KC_NUM), KC_PSLS, KC_PAST, KC_MPLY,
		KC_P7, KC_P8, KC_P9, KC_PMNS,
		KC_P4, KC_P5, KC_P6, KC_PPLS,
		KC_P1, KC_P2, KC_P3, KC_PENT,
		KC_P0, KC_PDOT),

	[_LIGHT] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, BL_UP,  BL_DOWN,  BL_TOGG,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
		KC_TRNS, KC_TRNS),

	[_EMPTY] = LAYOUT( // empty layer
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS)
};

void matrix_init_user(void) {
	//user init
}

void matrix_scan_user(void) {
	//user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

bool led_update_user(led_t led_state){
	return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [_LIGHT] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    [_EMPTY] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
};
#endif

