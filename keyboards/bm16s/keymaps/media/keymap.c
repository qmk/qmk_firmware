#include "bm16s.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_BRIU, _______, _______, KC_VOLU, \
		KC_BRID, _______, _______, KC_VOLD, \
		_______, _______, _______, KC_MUTE, \
		KC_MPRV, KC_MPLY, KC_MNXT, MO(1)    \
	),
	[1] = LAYOUT(
		RESET,   _______, _______, _______, \
		BL_TOGG, BL_DEC,  BL_INC,  BL_STEP, \
		RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, \
		RGB_SAI, RGB_SAD, _______, _______  \
	),
};