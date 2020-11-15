/* Copyright 2020 Lfgberg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ,-------------------------------------------------,
   * | c  | c  |    | u  |    | u  |    | m  |    | m  |
   * |----|----|----|----|----|----|----|----|----|----|
   * | c  |    |    | u  |    | u  |    | m  | m  | m  |
   * |----|----|----|----|----|----|----|----|----|----|
   * | c  | c  |    | u  | u  | u  |    | m  |    | m  |
   * ,-------------------------------------------------,
   */

  [0] = LAYOUT(
    KC_C, KC_C,  KC_U,       KC_U,  KC_M,       KC_M,
    KC_C,        KC_U,       KC_U,  KC_M, KC_M, KC_M,
    KC_C, KC_C,  KC_U, KC_U, KC_U,  KC_M,       KC_M
  ),
  [1] = LAYOUT(
    KC_TRNS, KC_TRNS,  KC_TRNS,           KC_TRNS,  KC_TRNS,           KC_TRNS,
    KC_TRNS,           KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS
  ),
  [2] = LAYOUT(
    KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS,  KC_TRNS,           KC_TRNS,
    KC_TRNS,            KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS
  ),
  [3] = LAYOUT(
    KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS,  KC_TRNS,           KC_TRNS,
    KC_TRNS,            KC_TRNS,           KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,           KC_TRNS
  )
};
