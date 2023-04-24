#include "quantum.h"

#include "quantum.h"

#if defined(ENCODER_ENABLE)

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_kb(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code_delay(KC_BRIU, 10);
        } else {
            tap_code_delay(KC_BRID, 10);
        }
    }
    return true;
}

#endif
