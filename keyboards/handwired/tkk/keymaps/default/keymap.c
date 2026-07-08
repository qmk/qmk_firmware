// Copyright 2022 Joe Fass (@jfass)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * L = left, R = right
     * T = thumb, I = index, M = middle, R = ring, P = pinky
     * 
     *             LP,            LR,              LM,            LI,             LT,            RT,            RI,             RM,             RR,             RP
     *
     */
    [0] = LAYOUT(
          LT(8, KC_A),   LT(7, KC_O),     LT(6, KC_E),   LT(5, KC_U), LT(10,KC_BSPC), LT(9, KC_SPC),   LT(1, KC_H),    LT(2, KC_T),    LT(3, KC_N),    LT(4, KC_S)
    ),
    [1] = LAYOUT(
                KC_Q,          KC_K,            KC_J,          KC_I,         KC_ESC,        KC_TAB,         KC_NO,        KC_RGUI,        KC_RGUI,        KC_RGUI
    ),
    [2] = LAYOUT(
                 KC_Z,          KC_Y,            KC_X,          KC_P,          KC_NO,         KC_NO,       KC_RCTL,          KC_NO,        KC_RCTL,        KC_RCTL
    ),
    [3] = LAYOUT(
              KC_QUOT,       KC_COMM,          KC_DOT,          KC_F,          KC_NO,         KC_NO,       KC_RALT,        KC_RALT,          KC_NO,        KC_RALT
    ),
    [4] = LAYOUT(
              KC_SCLN,       KC_LPRN,         KC_RPRN,        KC_GRV,          KC_NO,        MO(11),       KC_RSFT,        KC_RSFT,        KC_RSFT,          KC_NO
    ),
    [5] = LAYOUT(
              KC_LGUI,       KC_LGUI,         KC_LGUI,         KC_NO,   LGUI(KC_GRV),  LGUI(KC_TAB),          KC_D,           KC_G,           KC_C,         KC_ENT
    ),
    [6] = LAYOUT(
              KC_LCTL,       KC_LCTL,           KC_NO,       KC_LCTL,          KC_NO,         KC_NO,          KC_M,           KC_B,           KC_V,           KC_W
    ),
    [7] = LAYOUT(
              KC_LALT,         KC_NO,         KC_LALT,       KC_LALT,          KC_NO,         KC_NO,       KC_SLSH,           KC_L,           KC_R,        KC_BSLS
    ),
    [8] = LAYOUT(
                KC_NO,       KC_LSFT,         KC_LSFT,       KC_LSFT,         MO(11),         KC_NO,       KC_MINS,        KC_LBRC,        KC_RBRC,         KC_EQL
    ),
    [9] = LAYOUT(
                 KC_1,          KC_2,            KC_3,          KC_4,           KC_5,         KC_NO,       KC_LEFT,        KC_RGHT,          KC_UP,        KC_DOWN
    ),
    [10] = LAYOUT(
              KC_PGDN,       KC_PGUP,         KC_HOME,        KC_END,          KC_NO,          KC_6,          KC_7,           KC_8,           KC_9,           KC_0
    ),
    [11] = LAYOUT(
              MS_WHLD,       MS_WHLU,         MS_WHLL,       MS_WHLR,        MS_BTN2,       MS_BTN1,       MS_LEFT,        MS_RGHT,        MS_UP,          MS_DOWN
    )
};



