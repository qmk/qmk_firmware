// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,        KC_F7,   KC_F8,  KC_F9,   KC_F10, KC_F11,  KC_F12,  _______,
        _______, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,         KC_6,    KC_7,   KC_8,    KC_9,   KC_0,    KC_PSCR, _______,
        _______, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,         KC_Y,    KC_U,   KC_I,    KC_O,   KC_P,    KC_BSLS, _______,
        _______, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,         KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, _______,
        _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,         KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, _______,
        _______, KC_LCTL, KC_LALT, KC_LBRC, KC_RBRC,                                        KC_PLUS, KC_EQL, KC_RALT, KC_RCTL, _______,
                                                    LOWER,   KC_SPC,       KC_ENT,  RAISE,
                                                    KC_HOME, KC_BSPC,      KC_DEL,  KC_END,
                                                    KC_PGUP, KC_LGUI,      KC_RGUI, KC_PGDN  
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______, _______,
        _______, _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC,       KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______, _______,
        _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,      KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______, _______,
        _______, _______, _______, _______, KC_PAUS,                                          KC_P0,   KC_PDOT, KC_PEQL, _______, _______,
                                                     _______, _______,      _______, KC_PENT,
                                                     _______, _______,      _______, _______,
                                                     _______, _______,      _______, _______
    ),

    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______, KC_NUM,  KC_INS,  KC_SCRL, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______, KC_VOLU, KC_MNXT, _______, _______, _______, _______,
        _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,      _______, KC_MUTE, KC_MPLY, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,      _______, KC_VOLD, KC_MPRV, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______,
                                                     KC_MSTP, _______,      _______, RAISE,
                                                     _______, _______,      _______, _______,
                                                     _______, _______,      _______, _______
    )
};
