#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_S, KC_D,
		TO(1), KC_TILD),

	[1] = LAYOUT(
		RGB_TOG, RGB_MOD,
		TO(2), TO(0)),

	[2] = LAYOUT(
		RGB_HUD, RGB_HUI,
		TO(3), TO(1)),

	[3] = LAYOUT(
		RGB_SAD, RGB_SAI,
		TO(4), TO(2)),

	[4] = LAYOUT(
		RGB_VAD, RGB_VAI,
		TO(5), TO(3)),

	[5] = LAYOUT(
		KC_TRNS, KC_TRNS,
		RESET, TO(4))
};
