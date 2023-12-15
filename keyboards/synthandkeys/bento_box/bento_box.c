// Copyright 2023 Synth-and-Keys (@Synth-and-Keys)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    /*Main Encoder*/
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    /* TOP LEFT*/
    else if (index == 1) {
        if (clockwise) {
            tap_code16(C(KC_EQUAL));
        } else {
            tap_code16(C(KC_MINUS));
        }
    }
    /* TOP RIGHT*/
    else if (index == 2) {
        if (clockwise) {
            tap_code16(C(KC_Y));
        } else {
            tap_code16(C(KC_Z));
        }
    }
    return true;
}
#endif