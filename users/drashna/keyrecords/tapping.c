// Copyright 2021 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"

__attribute__((weak)) uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BK_LWER:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}

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

__attribute__((weak)) bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    // Immediately select the hold action when another key is pressed.
    // return true;
    // Do not select the hold action when another key is pressed.
    // return false;
    switch (keycode) {
//        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
//            return true;
        default:
            return true;
    }
}

__attribute__((weak)) bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    // Do not force the mod-tap key press to be handled as a modifier
    // if any other key was pressed while the mod-tap key is held down.
    // return true;
    // Force the mod-tap key press to be handled as a modifier if any
    // other key was pressed while the mod-tap key is held down.
    // return false;
    switch (keycode) {
        default:
            return true;
    }
}

__attribute__((weak)) bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}

__attribute__((weak)) bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}
