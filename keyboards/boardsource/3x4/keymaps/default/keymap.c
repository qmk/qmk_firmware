// Copyright 2022 @waffle87
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_0,   KC_1, KC_4, KC_7,
    KC_ENT, KC_2, KC_5, KC_8,
    MO(1),  KC_3, KC_6, KC_9
  ),
  [1] = LAYOUT(
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, QK_BOOT
  )
};
