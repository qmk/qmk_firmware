// Copyright 2025 Jack Sachinidhs (@jacksaxi)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(
        TO(_LAYER1),
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6,
        KC_7, KC_8, KC_9
    ),
    [_LAYER1] = LAYOUT(
        TO(_LAYER2),
        KC_Q, KC_W, KC_E,
        KC_R, KC_T, KC_Y,
        KC_U, KC_I, KC_O
    ),
    [_LAYER2] = LAYOUT(
        TO(_LAYER3),
        KC_A, KC_S, KC_D,
        KC_F, KC_G, KC_H,
        KC_J, KC_K, KC_L
    ),
    [_LAYER3] = LAYOUT(
        TO(_LAYER0),
        KC_Z, KC_X, KC_C,
        KC_V, KC_B, KC_N,
        KC_M, KC_COMM, KC_DOT
    )
};
