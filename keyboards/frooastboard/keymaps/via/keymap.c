#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_Z, KC_X,
		LT(1, KC_ESC), KC_TILD),

	[1] = LAYOUT(
		KC_F23, KC_F24,
		KC_TRNS, RGB_TOG)
};
