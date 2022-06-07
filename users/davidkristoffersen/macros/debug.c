// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

// Replace key records with macros
bool handle_test(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case KC_T0: {
        // Test QK_MAKE command
        SEND_STRING("qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP);
        break;
    }
    case KC_T1:
        // Test ascii characters
        SEND_STRING(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
        break;
    case KC_T2:
        // Test other characters
        tap_code16(NO_AE);
        tap_code16(NO_OE);
        tap_code16(NO_AA);
        tap_code16(LSFT(NO_AE));
        tap_code16(LSFT(NO_OE));
        tap_code16(LSFT(NO_AA));
        break;
    }
    return true;
};

bool process_debug(uint16_t keycode, keyrecord_t* record) {
    handle_false(handle_test(keycode, record));
    return true;
}
