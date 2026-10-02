// Copyright 2023 Duncan Sutherland (@dunk2k)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers{
    _QWERTY,
    _FN,
    _NUMPAD
};

#define LT1_BSPC LT(_FN, KC_BSPC)
#define OSM_CS OSM(MOD_LSFT | MOD_LCTL)
#define OSM_CA OSM(MOD_LCTL | MOD_LALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,        KC_Q,    KC_W,    KC_E,    KC_R,     KC_T, KC_LBRC,        KC_RBRC,     KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_TAB,        KC_A,    KC_S,    KC_D,    KC_F,     KC_G, G(KC_TAB),      TG(_NUMPAD), KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                              KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_RSFT),
        KC_LCTL,       KC_LALT, KC_LEFT, KC_RGHT,                                                               KC_UP,   KC_DOWN, KC_RALT, KC_RCTL,
                                                  LT1_BSPC, KC_SPC,  KC_HOME,         KC_PGUP, KC_ENT,  KC_DEL,
                                                  OSM_CS,   KC_LGUI, KC_END,          KC_PGDN, KC_RGUI, OSM_CA
    ),

    [_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,           KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TILD,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    LSA(KC_TAB), A(KC_TAB), KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR ,KC_PERC,  KC_CIRC,                         KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,
        _______, _______, KC_MPRV, KC_MNXT,                                                             KC_MPLY, KC_MSTP, _______, _______,
                                            _______, _______, _______,        _______, _______, KC_INS,
                                            _______, _______, _______,        _______, KC_PAUS, KC_PSCR
    ),

    [_NUMPAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,       _______, KC_NUM,  KC_P7,   KC_P8,   KC_P9,   _______, _______,
        _______, _______, _______, _______, _______, _______, QK_BOOT,       _______, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______,
        _______, _______, _______, _______, _______, _______,                         KC_PSLS, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______,
        _______, _______, _______, _______,                                                             KC_P0,   KC_PDOT, _______, _______,
                                            _______, _______, _______,       _______, _______, KC_PENT,
                                            _______, _______, _______,       _______, _______, _______
    )
};
