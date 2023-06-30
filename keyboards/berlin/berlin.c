#include "berlin.h"
#include "analog.h"
#include "qmk_midi.h"

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
    if (!dip_switch_update_user(index, active)) {
        return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { // ENC0 Button
        if(active) {
            tap_code(KC_MUTE);
        }
    } else if (index == 1) {
        if(active) {
                tap_code(KC_C);
        }
    }
    return true;
}

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { /* only run the slider function 1/256 times it's called */
        return;
    }
    midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN_A) >> 3));
}


void matrix_scan_user(void) {
    slider();
}
