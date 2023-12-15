// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_4x4(
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_P4,   KC_P5,   KC_P6,   KC_PERC,
    KC_P1,   KC_P2,   KC_P3,   KC_EQL,
    KC_P0,   MO(1),   KC_PDOT, KC_PENT
  ),
  [1] = LAYOUT_ortho_4x4(
    RGB_TOG, KC_PSLS, KC_PAST, KC_PMNS,
    KC_PGUP, KC_HOME, KC_UP,   KC_END,
    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,
    RGB_MOD, _______, KC_VOLD, KC_VOLU
  )
};
