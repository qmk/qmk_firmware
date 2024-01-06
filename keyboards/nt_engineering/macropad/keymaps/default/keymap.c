// Copyright 2023 Nick Taormina
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
  _MAIN,
  _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_4x3(
    KC_ENT, KC_0, KC_BSPC, 
    KC_7,   KC_8, KC_9,
    KC_4,   KC_5, KC_6, 
    KC_1,   KC_2, KC_3
  ),
  [_FN] = LAYOUT_ortho_4x3(
    KC_MPRV, KC_MPLY, KC_MNXT, 
    KC_CALC, KC_MYCM, KC_WHOM, 
    KC_BSLS, KC_PIPE, KC_TILDE, 
    KC_UNDO, C(KC_C), C(KC_V)
  )
};