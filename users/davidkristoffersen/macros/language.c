// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

#ifdef MULTI_LANGUAGE
// Handle conversion of special shift codes
bool handle_shift(uint16_t keycode, keyrecord_t* record) {
    if (get_mods() & MOD_MASK_SHIFT) {
        // Current active language
        int lang = get_language();
        // No action was needed
        if (lang == -1) return true;

        uint16_t converted_key = get_special_shifted_code(keycode, lang);
        if (converted_key != keycode) {
            // Tap new key while shift is disabled
            unregister_code(KC_LSFT);
            tap_code16(converted_key);
            register_code(KC_LSFT);
            return false;
        }
    }
    return true;
}

// Handle conversion of English to Norwegian codes
bool handle_language(uint16_t keycode, keyrecord_t* record) {
#if defined LAYER_EN && defined LAYER_NO
    int lang = get_language();
    if (lang == -1) return true;

    uint16_t converted_key = get_other_language_code(keycode, lang);
    if (converted_key != keycode) {
        // Disable old key and tap the new key
        unregister_code(keycode);
        tap_code16(converted_key);
        return false;
    }
#endif
    return true;
}

bool process_language(uint16_t keycode, keyrecord_t* record) {
    handle_false(handle_shift(keycode, record));
    handle_false(handle_language(keycode, record));
    return true;
}
#endif
