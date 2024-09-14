// Copyright 2023 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_1, KC_2,
    KC_3, KC_4,
    KC_5, KC_6,
    KC_7, MO(1)
  ),

  [1] = LAYOUT(
    QK_BOOT, KC_8,
    KC_9, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS
  )
};
