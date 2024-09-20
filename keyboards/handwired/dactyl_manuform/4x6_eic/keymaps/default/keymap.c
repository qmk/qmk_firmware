// Copyright 2023 Duncan Sutherland (@dunk2k)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _RAISE,
    _LOWER,
};
#define APP_P LSA(KC_TAB)
#define APP_N A(KC_TAB)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q, KC_W,    KC_E,    KC_R,    KC_T,    APP_P,        APP_N,  KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,    KC_GRV,
        KC_TAB,  KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME,      KC_END, KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
                       KC_LBRC, KC_RBRC,                                                         KC_MINS, KC_EQL,
                                         LOWER,   KC_SPC,                        KC_ENT,  RAISE,
                                         KC_TAB,  KC_BSPC,                       KC_DEL,  KC_LCTL,
                                         KC_CAPS, KC_LALT,                       KC_LGUI, KC_RSFT 
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, KC_PGUP, KC_LBRC, _______,      _______, KC_RBRC, KC_P7,   KC_P8, KC_P9, _______, KC_PLUS,
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_LPRN, _______,      _______, KC_RPRN, KC_P4,   KC_P5, KC_P6, KC_MINS, KC_PIPE,
        _______, _______, _______, _______, KC_PGDN, _______,                        _______, KC_P1,   KC_P2, KC_P3, KC_EQL,  KC_UNDS,
                          KC_PAUS, KC_PSCR,                                                            KC_P0, KC_PENT,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______
    ),

    [_RAISE] = LAYOUT(
        QK_BOOT, _______, _______, _______, KC_VOLU, _______, _______,      _______, _______, KC_NUM,  KC_INS,  KC_SCRL, _______, _______,
        _______, _______, _______, _______, KC_MUTE, _______, _______,      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        _______, _______, _______, _______, KC_VOLD, _______,                        _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______,
                                            _______, _______,                        _______, _______
    )
};
