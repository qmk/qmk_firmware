/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
 * SPDX-License-Identifier: GPL-2.0+
 */

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    }
    return true;
}
#endif

