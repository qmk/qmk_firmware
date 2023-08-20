// Copyright 2022 Vitaly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
qmk compile -kb avalanche/v1 -km default
qmk flash -kb avalanche/v1 -km default
*/

#include QMK_KEYBOARD_H

enum layer {
    LAYER_0,
    LAYER_1,
    LAYER_2,
};

#define FN_1 MO(LAYER_1)
#define FN_2 LT(LAYER_2, KC_SPC)
#define LFN_3 LSFT_T(KC_EQL)
#define RFN_3 RSFT_T(KC_MINS)
#define KC_QTSH RSFT_T(KC_QUOT)
#define EN_LALT LALT_T(KC_ENT)
#define EN_RALT RALT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_0] = LAYOUT(
                 KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
                 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_LGUI, KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_CAPS, KC_LSCR, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QTSH, KC_RBRC,
                 KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,  KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                                            KC_GRV,  LFN_3,   FN_2,    EN_LALT, EN_RALT, FN_1,    RFN_3,   KC_INS
    ),
    [LAYER_1] = LAYOUT(
                 _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_UP,   KC_PGUP, KC_PSCR, _______,
        _______, _______, KC_APP,  XXXXXXX, KC_HOME, KC_END,  KC_DEL,  _______, _______, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______, KC_F12,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS, _______, _______, KC_HOME, KC_END,  XXXXXXX, KC_PGDN, XXXXXXX, _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [LAYER_2] = LAYOUT(
                 _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
                 _______, KC_BSPC, KC_1,    KC_2,    KC_3,    XXXXXXX,                   XXXXXXX, XXXXXXX, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,
        _______, _______, KC_BSPC, KC_4,    KC_5,    KC_6,    KC_DEL,  _______, _______, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______, KC_F12,
                 _______, KC_BSPC, KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

