// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    
    if (!encoder_update_user(index, clockwise)) {
      return false;
    }
    
    if (clockwise) {
        tap_code(KC_WH_D);
    } else {
        tap_code(KC_WH_U);
    }
    
    return true;
}