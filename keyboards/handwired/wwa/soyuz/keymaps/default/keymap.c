// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"

enum custom_keycodes { 
    DEFAULT= SAFE_RANGE,SPOTIFY,DISCORD,CHROME/*,VLC*/
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,     KC_F10,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,   KC_F16,    KC_F17,
        KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,   KC_F23,    KC_F24 
    )
};

uint8_t divisor = 0;


void slider(void) {

    static int previousPotValue = 0;
    int currentPotValue = analogReadPin(POT1_PIN);
    int threshold = 25;  

    if (abs(currentPotValue - previousPotValue) > threshold) {
        midi_send_cc(&midi_device, 2, 0x0A, 0x7F - (currentPotValue >> 3));
        previousPotValue = currentPotValue;
    }


    static int previousPotValue2 = 0;
    int currentPotValue2 = analogReadPin(POT2_PIN);


    if (abs(currentPotValue2 - previousPotValue2) > threshold) {
        midi_send_cc(&midi_device, 3, 0x0B, 0x7F - (currentPotValue2 >> 3));
        previousPotValue2 = currentPotValue2;
    }


    static int previousPotValue3 = 0;
    int currentPotValue3 = analogReadPin(POT3_PIN);


    if (abs(currentPotValue3 - previousPotValue3) > threshold) {
        midi_send_cc(&midi_device, 4, 0x0C, 0x7F - (currentPotValue3 >> 3));
        previousPotValue3 = currentPotValue3;
    }
    
}

void matrix_scan_user(void) {
    slider();
}
