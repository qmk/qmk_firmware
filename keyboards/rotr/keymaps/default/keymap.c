#include "kb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_MPRV, KC_MPLY, KC_MNXT)
};

void encoder_update_user(uint8_t index, bool clockwise) {

	if (clockwise) {

		tap_code(KC_VOLU);

	} else {

		tap_code(KC_VOLD);

	}
}
