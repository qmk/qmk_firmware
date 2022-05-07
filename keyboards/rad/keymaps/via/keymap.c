#include QMK_KEYBOARD_H

#define ____ KC_TRNS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
		KC_SPC, KC_SPC, 
		KC_SPC, KC_SPC, KC_SPC, 
		KC_SPC, KC_SPC, KC_SPC, 
		KC_SPC, KC_SPC, KC_SPC),
		[1] = LAYOUT(
			    ____ , ____, 
                ____ , ____, ____,
                ____ , ____, ____,
				____ , ____, ____
		),
		[2] = LAYOUT(
			   ____ , ____, 
                ____ , ____, ____,
                ____ , ____, ____,
				____ , ____, ____
		),
		[3] = LAYOUT(
			    ____ , ____, 
                ____ , ____, ____,
                ____ , ____, ____,
				____ , ____, ____
		)
};



        