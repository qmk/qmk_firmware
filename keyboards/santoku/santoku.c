#include "santoku.h"

void encoder_update_kb(uint8_t index, bool clockwise) {
	if (clockwise) {
		tap_code(KC_WH_U);
	} else {
		tap_code(KC_WH_D);
	}
}
