#include "dead30.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    // Encoder 1, left
    if (index == 0 && clockwise) {
        tap_code(KC_PGDN);  // turned right
    } else if (index == 0) {
        tap_code(KC_PGUP);  // turned left
    }

    // Encoder 2, right
    else if (index == 1 && clockwise) {
        tap_code(KC_VOLU);  // turned right
    } else if (index == 1) {
        tap_code(KC_VOLD);  // turned left
    }
    return true;
}
