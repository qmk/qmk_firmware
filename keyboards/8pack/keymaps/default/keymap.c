#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
	    KC_V, KC_C, KC_X, MO(1),
		KC_A, KC_S, KC_D, KC_F
	),
	[1] = LAYOUT(
	    RGB_TOG, RGB_RMOD, RGB_MOD, KC_NO,
		QK_BOOT, BL_DOWN,  BL_UP,   BL_TOGG
	)
};
