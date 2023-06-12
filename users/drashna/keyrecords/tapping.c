// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"

#ifdef TAPPING_TERM_PER_KEY
__attribute__((weak)) uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BK_LWER:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}
#endif // TAPPING_TERM_PER_KEY

#ifdef PERMISSIVE_HOLD_PER_KEY
__attribute__((weak)) bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // Immediately select the hold action when another key is tapped:
    // return true;
    // Do not select the hold action when another key is tapped.
    // return false;
    switch (keycode) {
        default:
            return false;
    }
}
#endif // PERMISSIVE_HOLD_PER_KEY

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
__attribute__((weak)) bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    // Immediately select the hold action when another key is pressed.
    // return true;
    // Do not select the hold action when another key is pressed.
    // return false;
    switch (keycode) {
//        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
//            return true;
        default:
            return false;
    }
}
#endif // HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#ifdef QUICK_TAP_TERM_PER_KEY
__attribute__((weak)) uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return QUICK_TAP_TERM;
    }
}
#endif // QUICK_TAP_TERM_PER_KEY

#ifdef RETRO_TAPPING_PER_KEY
__attribute__((weak)) bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}
#endif // RETRO_TAPPING_PER_KEY
