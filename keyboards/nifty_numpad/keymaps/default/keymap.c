// Copyright 2023 Isaac Rex (@Acliad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layers 
// NOTE: LAYER_RGB is defined in nifty_numpad.h
enum LAYERS {
    LAYER_BL,
};

// Setup keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BL] = LAYOUT_numpad_6x6(
        KC_F13, KC_F19,    LT(LAYER_RGB, KC_BSPC), RGUI(KC_TAB), RGUI(KC_E), RGUI(RSFT(KC_S)),
        KC_F14, KC_F20,    KC_NUM,                 KC_PSLS,      KC_PAST,    KC_PMNS,
        KC_F15, KC_F21,    KC_P7,                  KC_P8,        KC_P9,      KC_PPLS,
        KC_F16, KC_F22,    KC_P4,                  KC_P5,        KC_P6,      
        KC_F17, KC_F23,    KC_P1,                  KC_P2,        KC_P3,      KC_PENT,
        KC_F18, KC_F24,    KC_P0,                                KC_PDOT
    ),
    
    [LAYER_RGB] = LAYOUT_numpad_6x6(
        _______, _______,    _______, RM_HUEU, RM_SATU, RM_VALU,
        _______, _______,    _______, RM_HUED, RM_SATD, RM_VALD,
        _______, _______,    _______, RM_NEXT, _______, RM_SPDU,
        _______, _______,    _______, _______, _______, 
        _______, _______,    _______, _______, _______, RM_SPDD,
        _______, _______,    _______,          _______     
    )
};
