#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_Z, KC_X,
		LT(1, KC_ESC), KC_TILD),

	[1] = LAYOUT(
		KC_F23, KC_F24,
		KC_TRNS, TO(2)),

	[2] = LAYOUT(
		RGB_TOG, RGB_MOD,
		TO(3), TO(0)),

	[3] = LAYOUT(
		RGB_HUD, RGB_HUI,
		TO(4), TO(2)),

	[4] = LAYOUT(
		RGB_SAD, RGB_SAI,
		TO(5), TO(3)),

	[5] = LAYOUT(
		RGB_VAD, RGB_VAI,
		TO(6), TO(4)),

	[6] = LAYOUT(
		KC_TRNS, KC_TRNS,
		RESET, TO(5))
};
