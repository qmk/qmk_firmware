// Copyright 2022 Marko Skakun <skakun.marko@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
};

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
};

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_LAYER0] = LAYOUT_3x5_5(
    KC_Q, KC_W, KC_E, KC_R, KC_T,                   KC_Y, KC_U, KC_I, KC_O, KC_P, 
    KC_A, KC_S, KC_D, KC_F, KC_G,                   KC_H, KC_J, KC_K, KC_L, KC_QUOT, 
    LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B,           KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), 
                    KC_LCTL, KC_LALT,               KC_RALT, KC_RCTL,
                    KC_BSPC, LT(2,KC_ESC), KC_DEL,  KC_TAB, LT(1,KC_ENT), KC_SPC),

[_LAYER1] = LAYOUT_3x5_5(
    KC_BSLS, KC_HOME, KC_UP, KC_END, KC_LBRC,       KC_RBRC, KC_P7, KC_P8, KC_P9, KC_LGUI, 
    KC_PSLS, KC_LEFT, KC_DOWN, KC_RGHT, KC_LPRN,    KC_RPRN, KC_P4, KC_P5, KC_P6, KC_ENT, 
    KC_LSFT, KC_SCLN, KC_QUOT, KC_MINS, KC_EQL,     KC_P0, KC_P1, KC_P2, KC_P3, KC_RSFT, 
                            KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, 
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

[_LAYER2] = LAYOUT_3x5_5(
    KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,              KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
    KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, 
    KC_F1, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_QUOT, KC_QUES, KC_TRNS, KC_F12, 
                            KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, 
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS) 

};