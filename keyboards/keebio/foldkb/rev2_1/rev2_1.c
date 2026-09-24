// Copyright 2025 Keebio (@keebio)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Disable the PD peripheral in pre-init because its pins are being used in the matrix:
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    // Call the corresponding _user() function (see https://docs.qmk.fm/#/custom_quantum_functions)
    keyboard_pre_init_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
