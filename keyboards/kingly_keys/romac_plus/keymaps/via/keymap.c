#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_7,  KC_8,  KC_9,
		KC_4,  KC_5,  KC_6,
		KC_1,  KC_2,  KC_3,
		MO(1), KC_0,  KC_DOT
	),
  
	[1] = LAYOUT(
		RGB_MOD,  KC_HOME,  KC_PGUP,
		KC_TRNS,  KC_END,   KC_PGDN,
		KC_TRNS,  KC_TRNS,  KC_TRNS,
		KC_TRNS,  KC_TRNS,  KC_ENT
	)
};
