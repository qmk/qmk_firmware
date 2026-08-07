// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_2x4_2(
        KC_A,         KC_B,      KC_C,         KC_D,            KC_N,       KC_M,        KC_L,      KC_K,
        KC_E,         KC_F,      KC_G,         KC_H,            KC_R,       KC_Q,        KC_P,      KC_O,
                                 KC_I,         KC_J,            KC_T,       KC_S
    ),
};
