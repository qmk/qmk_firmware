#include "rami_and_dudi_tomer.h"

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
			tap_code(KC_LEFT);
        } else {
            tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
			tap_code(KC_RGHT);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
}
