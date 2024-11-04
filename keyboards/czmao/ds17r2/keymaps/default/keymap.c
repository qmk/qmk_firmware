// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numberpad_5x4(
//1    2        3        4        
MO(1), KC_PSLS, KC_PAST, KC_PMNS,
KC_P7, KC_P8,   KC_P9,   
KC_P4, KC_P5,   KC_P6,   KC_PPLS,
KC_P1, KC_P2,   KC_P3,   
KC_P0,          KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT_numberpad_5x4(
KC_TRNS,   KC_NUM,  MO(2),   KC_CALC,
KC_HOME, KC_UP,   KC_PGUP, 
KC_LEFT, KC_TRNS, KC_RGHT, KC_TRNS,  
KC_END,  KC_DOWN, KC_PGDN, 
QK_RBT,           KC_TRNS, KC_TRNS
    ),
        [2] = LAYOUT_numberpad_5x4(
KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI,
RGB_TOG, RGB_SAI, KC_TRNS, 
RGB_HUD, KC_TRNS, RGB_HUI, RGB_VAD,  
KC_TRNS, RGB_SAD, KC_TRNS, 
RGB_MOD,          KC_TRNS, KC_TRNS
    )
    
    
};
