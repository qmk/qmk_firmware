// Copyright 2023 Nick Taormina
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "timer.h"
#define DEBOUNCE_MS 20 // debounce delay for rotary encoder switch

static uint32_t switch_timer;
bool            layer_switched = false;

void keyboard_pre_init_kb(void) {
    // turn on the LED backlight
    setPinOutput(GP3);
    writePinHigh(GP3);

    // turn off the power LEDs
    setPinOutput(GP25);
    writePinHigh(GP25);
    setPinOutput(GP16);
    writePinHigh(GP16);
    setPinOutput(GP17);
    writePinHigh(GP17);

    // turn on the RGB LED
    setPinOutput(GP11);
    writePinHigh(GP11);

    // set pin for rotary encoder switch
    setPinInputHigh(GP26);
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // set pin based on active status
    rgblight_enable();
    rgblight_sethsv(18, 255, 64);
    keyboard_post_init_user();
}

// Handles layer switching and RGB LED
void matrix_scan_user(void) {
    bool switch_pressed = !readPin(GP26);
    if (switch_pressed) {
        if (timer_elapsed32(switch_timer) > DEBOUNCE_MS) {
            if (!layer_switched) {
                layer_move(1); // Move to Layer 1
                rgblight_sethsv(4, 255, 64);
                layer_switched = true;
            } else {
                layer_move(0); // Move back to Layer 0
                rgblight_sethsv(40, 255, 64);
                layer_switched = false;
            }
            switch_timer = timer_read32();
        }
    }
}

// Handles rotary encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
