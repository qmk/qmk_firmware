// Copyright 2021 Shane Dowling (@shano)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_ENTS MT(MOD_LSFT, KC_ENT)
#define KC_FN   MO(_FN)

enum layers {
  _QWERTY,
  _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     //|----+----+----+----+----+----+              |----+----+----+----+----+----|
     KC_ESCC, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_ESC ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       KC_LALT,KC_LGUI,KC_SPC ,         KC_ENTS,KC_FN,KC_FN
  //                  `----+----+----'        `+---+----+----'c
  ),
  [_FN] = LAYOUT(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     _______,KC_1, KC_2 ,KC_3, KC_4,KC_5,               KC_6,KC_7,KC_8,KC_9,KC_0,KC_BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     _______,KC_EXCLAIM,KC_AT,KC_HASH,KC_DOLLAR,KC_PERCENT,      KC_LEFT,KC_DOWN, KC_UP ,KC_RIGHT,KC_LBRC,KC_RBRC,
  //|----+----+----+----+----+----+              |----+----+----+----+----+----|
     _______, KC_CIRCUMFLEX  , KC_AMPR  , KC_ASTERISK  , KC_LEFT_PAREN  , KC_RIGHT_PAREN  ,               KC_MINUS,KC_PLUS,KC_EQL,KC_PIPE,KC_GRAVE,KC_BACKSLASH,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       _______,_______,_______ ,         _______,_______,_______
  //                  `----+----+----'        `----+----+----'
  )
};

