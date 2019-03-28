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
  [base] = LAYOUT(
  //         ┌────────┬────────┬────────┐

                KC_1  ,  KC_2  ,  LC_3  ,

  //    ├────────┼────────┼────────┼────────┼

           KC_4  ,  KC_5  ,  KC_6  ,  KC_7  ,

  //    ├────────┼────────┼────────┼────────┼

                KC_8  ,  KC_9  ,  KC_0

  //         └────────┴────────┴────────┘
  ),
};
