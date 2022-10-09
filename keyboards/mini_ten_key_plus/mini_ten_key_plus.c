// Copyright 2021 minibois (@minibois)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mini_ten_key_plus.h"

/* Rotary Encoder's function (currently volume up/down) */
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
        if (clockwise) {
            tap_code16(KC_RIGHT_PAREN);
        } else {
            tap_code16(KC_LEFT_PAREN);
        }
    return true;
}