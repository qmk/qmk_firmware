/* Copyright 2018 Jack Hildebrandt
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

// Custom keycode definitions, and keycode renames
#define KC_oooo KC_TRNS
#define KC_XXXX KC_NO

// Layer names
#define base  0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // LAYOUT_kc() allows you to ommit the KC_ in front of a keycode.
  // If you want to use 'KC_', use LAYOUT() instead
  [base] = LAYOUT_kc(
  //         ┌────────┬────────┬────────┐

                  1   ,   2   ,    3    ,

  //    ├────────┼────────┼────────┼────────┼

            4    ,   5    ,    6   ,    7   ,

  //    ├────────┼────────┼────────┼────────┼

                  8   ,    9   ,    0

  //         └────────┴────────┴────────┘
  ),
};
