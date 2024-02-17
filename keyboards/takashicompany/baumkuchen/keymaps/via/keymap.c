// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        LT(1, KC_ESC), KC_Q, KC_W, KC_E, 
        KC_TAB, KC_A, KC_S, KC_D,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V,
        KC_WH_U, KC_WH_D
    ),

    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, MO(2), KC_TRNS,
        KC_TRNS,KC_TRNS
    ),

    [2] = LAYOUT(
        RGB_TOG, RGB_MOD, KC_TRNS, QK_BOOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,KC_TRNS
    )
};
