// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "static.h"

// Replace key records with macros
bool handle_dead_keys(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case TEST_0:
        // tap_code16(KC_0);
        break;
    case TEST_1:
        // tap_code16(KC_1);
        break;
    case TEST_2:
        // tap_code16(KC_2);
        break;
    }
    return true;
};

bool process_static(uint16_t keycode, keyrecord_t* record) {
    if (!handle_dead_keys(keycode, record)) {
        return false;
    }
    return true;
}
