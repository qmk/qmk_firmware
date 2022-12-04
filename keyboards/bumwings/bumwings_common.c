// Copyright 2022 Matthew A. Schnoor (@tubbytwins)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "bumwings_common.h"

/*
 * Handler for custom keycodes.
 */

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case HEX_0X: // Types "0x" for hexadecimal numbers
            if (record->event.pressed) {
                SEND_STRING("0x");
            }
            break;
    }
    return true;
}


/*
 * Handler for caps-word function.
 */

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

