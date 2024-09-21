// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT (
    KC_EQL, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_TAB,
    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LCBR,KC_RCBR,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
                    KC_LALT,KC_LGUI,KC_LCTL,KC_SPC, MO(1),  MO(1),  KC_BSPC,KC_DEL, KC_MEH, KC_RALT
),

[1] = LAYOUT (
    KC_PLUS,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,                KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_UNDS,
    MO(2),  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,  
    _______,KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,                 KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_BSLS,KC_DQUO,
    _______,KC_VOLD,KC_MUTE,KC_VOLU,KC_GRV, KC_TILD,KC_LBRC,KC_RBRC,KC_HOME,KC_END, KC_PGUP,KC_PGDN,KC_PIPE,_______, 
                    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______
),

[2] = LAYOUT (
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,QK_BOOT,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
                    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______
)
};
