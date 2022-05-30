// Copyright 2022 @whitefacemtn
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define LT2_ESC     LT(2, KC_ESC)
#define LT1_TAB     LT(1, KC_TAB)
#define LT1_ENT     LT(1, KC_ENT)
#define SFT_SLSH    MT(MOD_LSFT, KC_SLSH)
#define SFT_UP      MT(MOD_LSFT, KC_UP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        LT2_ESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, 
        LT1_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, LT1_ENT, 
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_UP,  
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT  
    ),

    [1] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  
        _______, KC_ESC,  _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PAST, KC_CALC, _______, 
        _______, _______, _______, _______, _______, _______, KC_DOT,  KC_1,    KC_2,    KC_3,    _______, KC_PGUP, 
        _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END   
    ),

    [2] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, 
        TO(1),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, KC_TILD, KC_BSLS, KC_VOLU, 
        _______, RESET,   _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  
    ),

};
