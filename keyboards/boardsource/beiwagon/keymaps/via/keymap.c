/* Copyright 2022 Boardsource
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _MAIN,
    _RAISE
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
     KC_7,  KC_8,  KC_9,
     KC_4,  KC_5,  KC_6,
     KC_1,  KC_2,  KC_3,
     KC_0,  KC_PENT,RAISE
  ),
  [_RAISE] = LAYOUT(
     KC_7,  KC_8,  RGB_TOG,
     KC_4,  KC_5,  RGB_MOD,
     KC_1,  KC_2,  KC_3,
     KC_0,  KC_PENT,_______
  ),
  [2] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
  ),
  [3] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______,
    _______, _______, _______
  )
};
