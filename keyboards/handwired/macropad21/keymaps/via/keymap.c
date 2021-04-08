//#include "../../macropad21.h"
//#include "config.h"
#include QMK_KEYBOARD_H
#include <quantum/keymap_extras/keymap_german.h>

enum keymap_layout {
    BASE = 0,
    SPECIAL,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[BASE] = LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R,
		KC_LSFT, KC_A, KC_S, KC_D, KC_F,
		KC_LALT, DE_Y, KC_C, KC_V,
		MO(SPECIAL), KC_SPC),

	[SPECIAL] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,
		KC_TRNS, DE_ODIA, DE_ADIA, DE_UDIA, DE_SS,
		KC_TRNS, LGUI(KC_D), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RESET, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_BTN1)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}
