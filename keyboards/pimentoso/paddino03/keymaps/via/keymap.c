/* Copyright 2020 Michele Ferri <zomgsako@gmail.com>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_VOLD, KC_VOLU),
  [1] = LAYOUT(KC_ESC, KC_HOME, KC_PGUP, KC_ENTER, KC_END, KC_PGDN, KC_VOLD, KC_VOLU),
  [2] = LAYOUT(MACRO00, MACRO01, MACRO02, MACRO03, MACRO04, MACRO05, KC_BRID, KC_BRIU),
  [3] = LAYOUT(MACRO06, MACRO07, MACRO08, MACRO09, MACRO10, MACRO11, KC_BRID, KC_BRIU),
};
