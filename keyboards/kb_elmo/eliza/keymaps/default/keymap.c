// Copyright 2022 kb-elmo<mail@elmo.space> (@kb-elmo)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    
        KC_LCTL,          KC_LALT,          KC_SPC,                    MO(1),            KC_RALT,          MO(2)
    ),
    [1] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT,          KC_BSLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPRV, KC_MNXT, KC_MPLY,    
        KC_TRNS,          KC_TRNS,          KC_TRNS,                   KC_TRNS,          KC_TRNS,          KC_TRNS
    ),
    [2] = LAYOUT(
        KC_GRV,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_PSCR,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,           KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,                   KC_TRNS,          KC_TRNS,          KC_TRNS
    ),
};
