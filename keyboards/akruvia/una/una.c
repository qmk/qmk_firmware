// Copyright 2023 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    setPinInputHigh(GP3);
    setPinInputHigh(GP2);
    keyboard_pre_init_user();
}

void matrix_scan_kb(void) {
    if (!readPin(GP3)) {
        register_code(KC_MS_BTN1);
    } else {
        unregister_code(KC_MS_BTN1);
    }
    if (!readPin(GP2)) {
        register_code(KC_MS_BTN2);
    } else {
        unregister_code(KC_MS_BTN2);
    }
    matrix_scan_user();
}
