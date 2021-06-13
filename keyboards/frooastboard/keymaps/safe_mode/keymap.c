#include "kb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(
		KC_S, KC_D, 
		TO(1), KC_TILD),

	KEYMAP(
		RGB_TOG, RGB_MOD, 
		TO(2), TO(0)),

	KEYMAP(
		RGB_HUD, RGB_HUI, 
		TO(3), TO(1)),

	KEYMAP(
		RGB_SAD, RGB_SAI, 
		TO(4), TO(2)),

	KEYMAP(
		RGB_VAD, RGB_VAI, 
		TO(5), TO(3)),

	KEYMAP(
		KC_TRNS, KC_TRNS, 
		RESET, TO(4))
	
};