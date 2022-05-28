// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "macros.h"

// Replace key records with macros
bool handle_test(uint16_t keycode, keyrecord_t* record) {
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

bool process_debug(uint16_t keycode, keyrecord_t* record) {
    handle_false(handle_test(keycode, record));
    return true;
}
