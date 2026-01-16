/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, KC_LALT, MO(1),   KC_SPC,  KC_SPC,  MO(2),   KC_TAB,  KC_DEL
    ),

    [1] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_MINS, _______, _______, KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, _______,
        _______, KC_TILD, _______, _______, _______, KC_UNDS, _______, _______, KC_PLUS, _______, _______, _______, KC_PIPE, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT(
        _______, _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,
        _______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    )

};
