// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "layouts.h"

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;:  |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,<  |  .>  |  /?  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |NumPad| GUI  | Lower| Space| Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
*/
#define qwerty_map LAYOUT_ortho_4x12(\
    KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,\
    KC_ESC,  KC_A,    KC_S,   KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT,\
    KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,\
    KC_LCTL, KC_LALT, numpad, KC_LGUI, lower,  KC_SPC, KC_SPC, raise,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT\
)

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  Q   |  W   |  F   |  P   |  G   |  J   |  L   |  U   |  Y   |  ;   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  A   |  R   |  S   |  T   |  D   |  H   |  N   |  E   |  I   |  O   |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  Z   |  X   |  C   |  V   |  B   |  K   |  M   |  ,   |  .   |  /   |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |NumPad| GUI  | Lower| Space| Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
*/
#define colemak_map LAYOUT_ortho_4x12(\
    KC_TAB,  KC_Q,    KC_W,   KC_F,    KC_P,  KC_G,   KC_J,   KC_L,  KC_U,    KC_Y,    KC_SCLN, KC_BSPC,\
    KC_ESC,  KC_A,    KC_R,   KC_S,    KC_T,  KC_D,   KC_H,   KC_N,  KC_E,    KC_I,    KC_O,    KC_ENT,\
    KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,   KC_K,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,\
    KC_LCTL, KC_LALT, numpad, KC_LGUI, lower, KC_SPC, KC_SPC, raise, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT\
)

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  "   |  ,   |  .   |  P   |  Y   |  F   |  G   |  C   |  R   |  L   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  A   |  O   |  E   |  U   |  I   |  D   |  H   |  T   |  N   |  S   |Return|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  ;   |  Q   |  J   |  K   |  X   |  B   |  M   |  W   |  V   |  Z   |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |NumPad| GUI  | Lower| Space| Space| Raise| Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
*/
#define dvorak_map LAYOUT_ortho_4x12(\
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,  KC_Y,   KC_F,   KC_G,  KC_C,    KC_R,    KC_L,  KC_BSPC,\
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,  KC_I,   KC_D,   KC_H,  KC_T,    KC_N,    KC_S,  KC_ENT,\
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,  KC_X,   KC_B,   KC_M,  KC_W,    KC_V,    KC_Z,  KC_SLSH,\
    KC_LCTL, KC_LALT, numpad,  KC_LGUI, lower, KC_SPC, KC_SPC, raise, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT\
)

/* Lower - Normal
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |  !   |  @   |  #   |  $   |  %   |  ^   |  &   |  *   |  (   |  )   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  _   |  +   |  {   |  }   |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | End  | Home | XXXX | XXXX |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
*/
#define normal_lower_map LAYOUT_ortho_4x12(\
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,\
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_END,  KC_HOME, XXXXXXX, XXXXXXX, _______,\
    _______, _______, _______, _______, _______, _______, _______, adjust,  KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY\
)

/* Raise - Normal
 * ,-----------------------------------------------------------------------------------.
 * |  `   |  1   |  2   |  3   |  4   |  5   |  6   |  7  |   8   |  9   |  0   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  -   |  =   |  [   |  ]   |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  #   |  \   | PgDn | PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
*/
#define normal_raise_map LAYOUT_ortho_4x12(\
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,\
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,\
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12,  KC_HASH, KC_BSLS, KC_PGDN, KC_PGUP, _______,\
    _______, _______, _______, _______, adjust, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY\
)
