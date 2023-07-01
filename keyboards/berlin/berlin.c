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

int16_t slider_a_prev_value = 0;
int16_t slider_b_prev_value = 0;
int16_t slider_c_prev_value = 0;

#define slider_tolerance 8

int kill_in_tolerance(int value, int previousValue) {
    return ( value < previousValue-slider_tolerance || value > previousValue+slider_tolerance);
}

int slower_downer = 0;

void slider(void) {
    slower_downer++;
    if (slower_downer % 16 != 0) {
        return; // Only execute every 16th time to reduce noise.
    }
    int16_t slider_a_value = analogReadPin(SLIDER_PIN_A);
    int16_t slider_b_value = analogReadPin(SLIDER_PIN_B);
    int16_t slider_c_value = analogReadPin(SLIDER_PIN_C);

    if (kill_in_tolerance(slider_a_value, slider_a_prev_value) ) {
        slider_a_prev_value = slider_a_value;
        midi_send_cc(&midi_device, 0, 0x01, (slider_a_value >> 3));
    }

    if (kill_in_tolerance(slider_b_value, slider_b_prev_value) ) {
        slider_b_prev_value = slider_b_value;
        midi_send_cc(&midi_device, 0, 0x02, (slider_b_value >> 3));
    }

    if (kill_in_tolerance(slider_c_value, slider_c_prev_value) ) {
        slider_c_prev_value = slider_c_value;
        midi_send_cc(&midi_device, 0, 0x03, (slider_c_value >> 3));
    }
}

void matrix_scan_user(void) {
    slider();
}
