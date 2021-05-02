#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( 
		KC_A, KC_B, KC_C, KC_D, \
		KC_PLUS, KC_SLSH, KC_ASTR, KC_MINS, \
		KC_7, KC_8, KC_9, KC_PGUP, \
		KC_4, KC_5, KC_6, KC_PGDN, \
		KC_1, KC_2, KC_3, KC_INS, \
		RESET, KC_0, KC_DEL,KC_ENT )
};
