// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE 0
#define _MACRO1 1
#define _MACRO2 2
#define _MACRO3 3

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// entirely and just use numbers.


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT( /*Base*/
         KC_ESC, KC_A, KC_B, KC_C, KC_V, KC_W, KC_X, KC_Y,
         KC_DEL, KC_D, KC_E, KC_F, KC_Z, KC_P0, KC_PAST, KC_PSLS,
         KC_G, KC_H, KC_I, KC_J, KC_P7, KC_P8, KC_P9, KC_PMNS,
         KC_K, KC_L, KC_M, KC_N, KC_P4, KC_P5, KC_P6, KC_PPLS,
         KC_O, KC_P, KC_Q, KC_R, KC_P1, KC_P2, KC_P3,
         TO(1), KC_S, KC_T, KC_U, KC_P0, KC_PDOT, KC_COMM, KC_PENT
    ),

    [_MACRO1] = LAYOUT(
        KC_ESC, KC_P0, KC_P0, KC_P0,    KC_P0, KC_P0, KC_P0, KC_P0,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_P0, KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS,
         TO(0), KC_P0, KC_P0, KC_P0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_MACRO2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_MACRO3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
