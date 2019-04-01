#include "romac.h"

#define _BASE 0
#define _FN1 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = LAYOUT_ortho_3x4(
		KC_7, KC_8, KC_9, \
		KC_4, KC_5, KC_6, \
		KC_1, KC_2, KC_3, \
		MO(_FN1), KC_0, KC_ENT) \
	),
	[_1] = LAYOUT_ortho_3x4(
		KC_TRNS, KC_HOME, KC_PGUP, \
		KC_TRNS, KC_END, KC_PGDN, \
		KC_TRNS, KC_TRNS, KC_TRNS, \
		KC_TRNS, KC_TRNS, KC_DOT) \
	)

};

