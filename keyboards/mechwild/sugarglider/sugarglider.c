// Copyright 2022 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sugarglider.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
    }
    return true;
}
#endif
