// Copyright 2023 Duncan Sutherland (@dunk2k)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define APP_P LSA(KC_TAB)
#define APP_N A(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,  APP_P,        APP_N,   KC_F7,  KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_6,  KC_5,   KC_LCBR,      KC_RCBR, KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_LBRC,      KC_RBRC, KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_LPRN,      KC_RPRN, KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,                          KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_UP, KC_DOWN,                                                      KC_LEFT, KC_RGHT, KC_RALT, KC_RCTL,
                                            RAISE, KC_SPC, KC_HOME,      KC_END,  KC_ENT, LOWER,
                                                  KC_BSPC, KC_LGUI,      KC_RGUI, KC_DEL
    ),

    [_LOWER] = LAYOUT(
        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, _______,        _______,KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,
        _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,KC_MUTE,
        _______,KC_EQL,KC_UNDS,KC_MINS,KC_PLUS,_______,_______,         _______,_______,_______,_______,_______,_______,KC_VOLU,
        _______,KC_HOME,KC_PGDN,KC_PGUP,KC_END,_______,_______,         _______,_______,KC_MPRV,KC_MPLY,KC_MNXT,KC_MSTP,KC_VOLD,
        _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,                                                        _______,_______,_______,QK_BOOT,
                                        _______,_______,_______,        _______,_______,_______,
                                                _______,_______,        _______,_______
        
    ),

    [_RAISE] = LAYOUT(
        _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,        _______,KC_NUM, KC_P7 , KC_P8 , KC_P9 ,_______,_______, 
        _______,KC_INS,KC_SCRL,KC_PAUS,KC_PSCR,_______,_______,        _______,KC_PAST, KC_P4 , KC_P5 , KC_P6 ,KC_PPLS,_______,
        _______,_______,_______,_______,_______,_______,                       KC_PSLS, KC_P1 , KC_P2 , KC_P3 ,KC_PMNS,_______,
        QK_BOOT,_______,_______,_______,                                                         KC_P0,KC_PDOT,_______,_______,
                                        _______,_______,_______,        _______,KC_PENT,_______,
                                                _______,_______,        _______,_______
    )
};