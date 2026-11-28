// Copyright 2026 Nick Getka (@NickGetka)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "custom.h"

enum custom_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ergodox_pretty(
    // left hand
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
    KC_ESC,  C(KC_LALT), KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_UP,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    // right hand
    KC_NO,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_NO,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_NO,   RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_ENT,
             KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),

[_LOWER] = LAYOUT_ergodox_pretty(
    // left hand
    KC_TILD, KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_NO,
    _______, KC_PIPE, KC_BSLS, KC_PLUS, KC_SCLN, KC_EQL,  KC_NO,
    _______, KC_MINS, KC_SLSH, KC_QUES, KC_COLN, KC_QUOT,
    _______, _______, _______, _______, _______, _______, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    // right hand
    KC_NO,   KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, _______,
    KC_NO,   KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,
             KC_DQUO, KC_COMM, KC_DOT,  KC_LBRC, KC_RBRC, _______,
    KC_NO,   _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,
             KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),

[_RAISE] = LAYOUT_ergodox_pretty(
    // left hand
    KC_PERC, KC_MINS, KC_1,    KC_2,    KC_3,    KC_EQL,  KC_NO,
    _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_PAST, KC_NO,
    _______, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_DOT,
    KC_SLSH, _______, _______, _______, _______, _______, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_LEFT, KC_UP,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    // right hand
    KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,  _______,
    KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
             _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, _______,
             KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),

[_ADJUST] = LAYOUT_ergodox_pretty(
    // left hand
    _______, _______, _______, _______, _______, _______, KC_NO,
    _______, KC_MUTE, KC_VOLD, KC_VOLU, LCA(KC_LEFT), _______, KC_NO,
    _______, KC_BRID, KC_BRIU, _______, _______, _______,
    QK_BOOT, _______, _______, _______, _______, _______, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    // right hand
    KC_NO,   _______, _______, _______, _______, KC_PSCR, UG_TOGG,
    KC_NO,   KC_MPRV, LCA(KC_RGHT), KC_MPLY, KC_MNXT, _______, _______,
             _______, _______, _______, _______, _______, _______,
    KC_NO,   _______, _______, _______, _______, _______, _______,
             _______, _______, KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
