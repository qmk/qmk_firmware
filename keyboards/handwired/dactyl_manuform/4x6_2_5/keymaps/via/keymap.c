// Copyright 2021 Andrzej Kotulski (@akotulski)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _RAISE,
    _LOWER,
    _BLANK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
         KC_ESC,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,                                KC_Y,   KC_U,    KC_I,   KC_O,    KC_P, KC_BSLS,
         KC_TAB,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,                                KC_H,   KC_J,    KC_K,   KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,                                KC_N,   KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_GRV, KC_LBRC, KC_RBRC,                                                               KC_MINS, KC_EQL,  KC_APP, KC_RCTL,
                                           KC_SPC,   MO(2), KC_HOME,             KC_END,  MO(1), KC_ENT,
                                                   KC_BSPC, KC_LALT,            KC_LGUI, KC_DEL
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, KC_LBRC,                                KC_RBRC, KC_P7,   KC_P8,   KC_P9,   QK_BOOT,   KC_PLUS,
        _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END , KC_LPRN,                                KC_RPRN, KC_P4,   KC_P5,   KC_P6,   KC_MINS, KC_PIPE,
        _______, _______, _______, _______, _______, _______,                                _______, KC_P1,   KC_P2,   KC_P3,   KC_EQL,  KC_UNDS,
        _______, _______, _______, KC_PSCR,                                                                    _______, KC_P0, _______, _______,
                                            _______, _______,  _______,             _______, _______, _______,
                                                      _______, _______,             _______, _______
    ),

    [_RAISE] = LAYOUT(
        _______, QK_BOOT, _______, _______, _______, _______,                                _______, _______,  KC_NUM,  KC_INS, KC_SCRL, KC_MUTE,
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, _______,                                _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLU,
        _______, _______, _______, _______, _______, _______,                                _______, _______, _______, _______, _______, KC_VOLD,
        _______, _______, _______, _______,                                                                     KC_EQL, _______, _______, _______,
                                            _______, _______, _______,              _______, _______, _______,
                                                     _______, _______,              _______, _______
    ),
    [_BLANK] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,                                                                    _______, _______, _______, _______,
                                            _______, _______, _______,              _______, _______, _______,
                                                     _______, _______,              _______, _______
    )
};
