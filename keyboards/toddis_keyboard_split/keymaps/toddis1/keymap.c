// Copyright 2021 torbjorn rasmusson (@torbjorn rasmusson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    // left hand 
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    	               KC_A, KC_B, KC_D,

    // right hand 
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_D
    ),
    [_FN] = LAYOUT(
    // left hand 
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    	               KC_A, KC_B, KC_D,

    // right hand 
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F,
    KC_A,  KC_B, KC_D
    ),
};
