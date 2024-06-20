// Copyright 2012 Jun Wako <wakojun@gmail.com>
// Copyright 2021 Dmitriy Kuminov (@dmik)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define APP_P A(KC_TAB)
#define APP_N LSA(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_ESC,  KC_1,  KC_2,    KC_3,    KC_6,    KC_5,                          KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_CAPS, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
        KC_LALT, APP_P, KC_LEFT, KC_RGHT,                                                          KC_UP,   KC_DOWN, APP_N,   KC_RALT,
                                          RAISE,   KC_SPC, KC_LSFT,      KC_RSFT, KC_ENT,  LOWER,
                                          KC_HOME, KC_BSPC,KC_LGUI,      KC_RGUI, KC_DEL,  KC_END
    ),

    [_LOWER] = LAYOUT(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                       KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
        _______,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,                     KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
        _______,_______,_______,_______,KC_PGUP,_______,                     KC_NUM, KC_P7,  KC_P8,  KC_P9,  KC_PMNS,_______,
        _______,KC_SCRL,KC_INS, KC_PAUS,KC_PSCR,_______,                     KC_PAST,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,_______,
        _______,_______,_______,_______,KC_PGDN,_______,                     KC_PSLS,KC_P1,  KC_P2,  KC_P3,  KC_PENT,_______,
        _______,_______,_______,_______,                                                     KC_P0,  KC_PDOT,_______,_______,
                                        _______,_______,_______,     _______,_______,_______,
                                        _______,_______,_______,     _______,_______,_______
    ),

    [_RAISE] = LAYOUT(
        KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                       KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
        _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,KC_VOLU,KC_LBRC,                     KC_RBRC,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,KC_MUTE,KC_LPRN,                     KC_RPRN,KC_MNXT,KC_MPRV,KC_MPLY,_______,_______,
        _______,_______,_______,_______,KC_VOLD,KC_LCBR,                     KC_RCBR,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,                                                     _______,_______,_______,_______,
                                        _______,_______,_______,     _______,_______,_______,
                                        _______,_______,_______,     _______,_______,_______
    )
};
