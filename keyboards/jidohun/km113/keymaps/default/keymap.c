// Copyright 2023 wind (@yelishang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,                  KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,                  TO(0),    KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                   TO(1),    KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,                    TO(2),    KC_PGUP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             MO(1),   KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, TO(3),    KC_PGDN
    ),

    [1] = LAYOUT(
        EE_CLR,           KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV,  KC_MPLY, KC_MNXT, KC_MAIL, KC_WHOM, KC_MYCM, KC_CALC,
        _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, RM_PREV,  RM_NEXT, _______,                 _______,
        _______, _______, _______, _______, RM_NEXT, _______, _______, KC_PSCR,  KC_PGUP, KC_DEL,  _______, _______, _______, _______,                  TO(0),   _______,
        _______, _______, _______, _______, _______, _______, _______, KC_INS,   KC_PGDN, KC_END,  _______, _______,          _______,                  TO(1),   _______,
        _______,          _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, RM_VALU,                  TO(2),   _______,
        _______, GU_TOGG, _______,                           RM_TOGG,                              _______, _______, _______, RM_SPDD, RM_VALD, RM_SPDU,TO(3),   _______
    ),

    [2] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,                  KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,                  TO(0),    KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                   TO(1),    KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,                    TO(2),    KC_PGUP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             _______, KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, TO(3),    KC_PGDN
    ),

    [3] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,                  KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,                  TO(0),    _______,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                   TO(1),    _______,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,                    TO(2),    _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             _______, KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, TO(3),    _______
    )
};
