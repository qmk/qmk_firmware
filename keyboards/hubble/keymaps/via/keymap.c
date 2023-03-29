// Copyright 2022 Anton Chernenko (@ch3rny)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


enum layers {
  BASE,
  LOWER,
  RAISE,
  ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
       KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_INS,  KC_PGUP, 
       KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_DEL,  KC_PGDN, 
       KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(LOWER),        KC_UP,
       KC_LCTL, KC_LGUI, KC_LALT, LT(LOWER, KC_BSPC),   LT(ADJUST, KC_ENT),    LT(RAISE, KC_SPC),KC_RALT,MO(RAISE),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [LOWER] = LAYOUT(
       KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PPLS, KC_EQL,  _______, KC_HOME, 
       _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PMNS, _______,          _______, KC_END, 
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,      
       _______, _______, _______, _______,          _______,          _______,          _______, _______, _______,          _______, _______, _______
    ),

    [RAISE] = LAYOUT(
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, _______, _______, 
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, 
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,      
       _______, _______, _______,          _______, _______, _______,                   _______, _______, _______,          _______, _______, _______
    ),

    [ADJUST] = LAYOUT(
       QK_BOOT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_RBT,  RGB_HUI, RGB_SAI, 
       _______, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,          RGB_HUD, RGB_SAD, 
       _______, VK_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_VAI,      
       _______, _______, _______,          _______, _______, _______,                   _______, _______, _______,         RGB_RMOD, RGB_VAD, RGB_MOD
    ),
};
