// Copyright 2022 Commander1024 (@Commander1024)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

// rotary encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Volume control
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return false;
};
