#include "rami_and_dudi_v2.h"

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) { /* Second encoder */
		if (clockwise) {
		tap_code16(C(KC_Z));
						}
		else {
		tap_code16(C(KC_Y));
			}
							}
														}


