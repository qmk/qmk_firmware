// Copyright 2025 Keebio (@keebio)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN1 1
#define _FN2 2

#define FN1 MO(_FN1)
#define FN2 MO(_FN2)
#define SP_FN1 LT(_FN1, KC_SPACE)
#define SP_FN2 LT(_FN2, KC_SPACE)
#define BS_FN1 LT(_FN1, KC_BSPC)
#define BS_FN2 LT(_FN2, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_DEL,   KC_BSPC,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_QUOT,  KC_ENT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    KC_LCTL,  KC_LALT,  KC_LGUI,  FN1,      SP_FN1,   BS_FN2,   KC_RGUI,  KC_RALT,  FN2,      KC_RCTL
  ),

  [_FN1] = LAYOUT(
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,
    QK_BOOT,  UG_HUEU,  UG_SATU,  UG_VALU,  KC_VOLU,  KC_LBRC,  KC_RBRC,  KC_4,     KC_5,     KC_6,     KC_SCLN,  _______,
    UG_NEXT,  UG_HUED,  UG_SATD,  UG_VALD,  KC_VOLD,  KC_LCBR,  KC_RCBR,  KC_1,     KC_2,     KC_3,     KC_UP,    _______,
    UG_TOGG,  _______,  _______,  _______,  _______,  KC_DEL,   KC_0,     KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_FN2] = LAYOUT(
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,  KC_PLUS,
    _______,  _______,  _______,  KC_INS,   KC_PGUP,  KC_HOME,  _______,  _______,  _______,  _______,  KC_COLN,  _______,
    _______,  _______,  _______,  KC_DEL,   KC_PGDN,  KC_END,   _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  KC_DEL,   _______,  _______,  _______,  _______,  _______
  )
};
