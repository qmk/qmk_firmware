// Copyright 2024 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_all(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_RSFT, MO(2),
    KC_LCTL, KC_LGUI, KC_LALT,          LT(1, KC_SPC),  KC_SPC,                    KC_RALT, MO(1), KC_RCTL
),
[1] = LAYOUT_all(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
    _______, _______, _______, _______, _______, KC_SLSH, KC_SCLN, KC_QUOT, KC_DOT,  KC_UP, _______,
    _______, _______, _______,          _______, _______,                   KC_LEFT, KC_DOWN, KC_RIGHT
),
[2] = LAYOUT_all(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8, _______, _______,  _______, _______, _______, _______,
    KC_CAPS, KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, _______, _______, _______,  _______, _______,
    _______, _______, _______,          _______, _______,                   KC_PGUP, _______, KC_PGDN
)
};