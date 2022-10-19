// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

bool handle_language(uint16_t keycode) {
#ifdef LAYER_NO
    // Handle conversion of English to Norwegian codes
    uint16_t org_keycode = keycode;
    keycode = get_norwegian_code(keycode);
#endif

#ifndef NO_SPECIAL_SHIFT
    // Handle conversion of special shift codes
    if (get_mods() & MOD_MASK_SHIFT) {
        uint16_t shifted_key = get_special_shifted_code(keycode);
        if (shifted_key != keycode) {
            // Tap shifted key while shift is disabled
            unregister_code(KC_LSFT);
            tap_code16(shifted_key);
            register_code(KC_LSFT);
            return false;
        }
    }
#endif

#ifdef LAYER_NO
    // Tap new language key
    if (keycode != org_keycode) {
        tap_code16(keycode);
        return false;
    }
#endif
    return true;
}

bool process_language(uint16_t keycode, keyrecord_t* record) {
    HANDLE_FALSE(handle_language(keycode));
    return true;
}
