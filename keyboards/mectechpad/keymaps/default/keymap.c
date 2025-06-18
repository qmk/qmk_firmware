// Copyright 2025 Jack Sachinidhs (@jacksaxi)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3
};

// Define the keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6,
        KC_7, KC_8, KC_9,
        TO(_LAYER1)
    ),
    [_LAYER1] = LAYOUT(
        KC_Q, KC_W, KC_E,
        KC_R, KC_T, KC_Y,
        KC_U, KC_I, KC_O,
        TO(_LAYER2)
    ),
    [_LAYER2] = LAYOUT(
        KC_A, KC_S, KC_D,
        KC_F, KC_G, KC_H,
        KC_J, KC_K, KC_L,
        TO(_LAYER3)
    ),
    [_LAYER3] = LAYOUT(
        KC_Z, KC_X, KC_C,
        KC_V, KC_B, KC_N,
        KC_M, KC_COMM, KC_DOT,
        TO(_LAYER0)
    ),
};
