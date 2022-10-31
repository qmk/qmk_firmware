// Copyright 2022 Makoto Kurauchi (@MakotoKurauchi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
  _BASE = 0,
};

enum {
  TD_AB = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_AB]  = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_1x1(
    TD(TD_AB)
  )
};
