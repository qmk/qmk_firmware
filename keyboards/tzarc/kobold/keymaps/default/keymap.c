// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x4(
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L,
        KC_M, KC_N, KC_O, KC_P
    ),
};
// clang-format on
