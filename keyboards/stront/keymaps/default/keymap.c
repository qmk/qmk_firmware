// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _MOD,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        LT(_MOD, KC_Q), LCTL_T(KC_E)
    ),

    [_MOD] = LAYOUT(
        _______,         LSFT_T(KC_CAPS)
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MOD] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
// clang-format on
