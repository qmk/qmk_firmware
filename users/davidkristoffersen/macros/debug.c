// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

// Replace key records with macros
bool handle_test(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case KC_T0:
        // tap_code16(KC_0);
        SEND_STRING("qmk compile -kb planck/rev5 -km prog_qgmlwb");
        break;
    case KC_T1:
        SEND_STRING("-");
        // tap_code16(KC_1);
        return false;
        // break;
    case KC_T2:
        tap_code16(NO_MINS);
        return false;
        // break;
    }
    return true;
};

bool process_debug(uint16_t keycode, keyrecord_t* record) {
    handle_false(handle_test(keycode, record));
    return true;
}
