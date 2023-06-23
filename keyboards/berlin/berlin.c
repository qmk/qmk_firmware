#include "berlin.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* Top Left Encoder, volume control */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Top Right Display Encoder, not yet implemented */
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
    }
    return true;
}


bool dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
        case 0: // ENC0 Switch
            if(active) {
                tap_code(KC_MUTE);
            }
    }
    return false;
}
