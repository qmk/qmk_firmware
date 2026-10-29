// Copyright 2018-2021
// ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
// David Philip Barr <@davidphilipbarr>
// Pierre Chevalier <pierrechevalier83@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H

/* Base layer 0 layout uses home row mods. See the following guide for details:
 * https://precondition.github.io/home-row-mods
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    CTL_T(KC_A),ALT_T(KC_S),GUI_T(KC_D),SFT_T(KC_F), KC_G,    KC_H, SFT_T(KC_J),GUI_T(KC_K),ALT_T(KC_L),CTL_T(KC_SCLN),
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          LT(2,KC_TAB), KC_ENT,      KC_SPC,  LT(1,KC_BSPC)
    ),
    [1] = LAYOUT_split_3x5_2(
    KC_INS,  KC_1,    KC_2,    KC_3,    KC_VOLU,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DQUO,
    KC_DEL,  KC_4,    KC_5,    KC_6,    KC_VOLD,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    KC_CAPS, KC_7,    KC_8,    KC_9,    KC_0,        _______, _______, _______, _______, _______,
                               MO(3),   QK_GESC,     _______, _______
    ),
    [2] = LAYOUT_split_3x5_2(
    _______, KC_LBRC, KC_LCBR, KC_RCBR, _______,     KC_CIRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_TILD,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_AMPR, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
    _______, _______, _______, _______, _______,     KC_ASTR, KC_UNDS, KC_PLUS, KC_PIPE, _______,
                               _______, _______,     KC_DEL,  MO(3)
    ),
    [3] = LAYOUT_split_3x5_2(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,      _______, MS_WHLU, MS_WHLD, _______, QK_BOOT,
    _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,      MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_INS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F12,      _______, MS_BTN1, MS_BTN2, _______, _______,
                               _______, _______,     _______, _______
    )
};

