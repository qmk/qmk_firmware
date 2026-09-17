// Copyright 2024 suikagiken (@suikagiken)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                            KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL , 
        C(KC_X), KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_PSCR,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_BSPC, 
        C(KC_C), KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,          KC_EQL ,          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS, KC_ENT , 
        C(KC_V), KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_LBRC,          KC_RBRC, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,  
                 KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,          KC_UP  ,          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,  
                          KC_LCTL, KC_LWIN, KC_LOPT, MO(1)  , KC_SPC , KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC , MO(1)  , KC_ROPT, KC_APP , KC_RCTL  
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,  
                 _______, _______, _______, _______, _______, _______,          KC_PGUP,          _______, _______, _______, _______, _______, _______,  
                          _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END , _______, _______, _______, _______, _______  
    )
};
