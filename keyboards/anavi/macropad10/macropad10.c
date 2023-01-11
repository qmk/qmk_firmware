// Copyright 2022 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "encoder.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
#endif

