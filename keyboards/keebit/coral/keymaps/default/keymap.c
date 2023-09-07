// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Thumb Keys
#define L_THUMB LT(LowerLayer, KC_ENTER)
#define R_THUMB LT(RaiseLayer, KC_SPACE)

// Rotary
#define L_ROT KC_MNXT
#define R_ROT KC_MPLY


enum Layers {
    BaseLayer,
    LowerLayer,
    RaiseLayer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BaseLayer] = LAYOUT(
        KC_GRV,  KC_1, KC_2,    KC_3,    KC_4,    KC_5,           /**/        KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_GRV,
        KC_ESC,  KC_Q, KC_W,    KC_E,    KC_R,    KC_T,           /**/        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,  KC_A, KC_S,    KC_D,    KC_F,    KC_G,           /**/        KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,    KC_B,           /**/        KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                       KC_LGUI, KC_LALT, KC_LCTL, L_THUMB, L_ROT, /**/ R_ROT, R_THUMB, KC_RCTL, KC_RALT, KC_RGUI
    ),
    [LowerLayer] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            /**/          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             /**/          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          /**/          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        _______, KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,          /**/          KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                          _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),
    [RaiseLayer] = LAYOUT(
        _______, _______, _______, _______, _______,  _______,          /**/          _______, _______, _______, _______, _______, _______,
        _______, KC_INS,  KC_PSCR, KC_APP,  XXXXXXX,  XXXXXXX,          /**/          KC_PGUP, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, KC_BSPC,
        _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  KC_CAPS,          /**/          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_BSPC,
        _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE, XXXXXXX,          /**/          XXXXXXX, KC_HOME, XXXXXXX, KC_END,  XXXXXXX, _______,
                          _______, _______, _______,  _______, _______, /**/ _______, _______, _______, _______, _______
    )
};
