/*
Copyright 2020 Ckat <ckat@teknik.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

/* RIGHT
            +---------------------------------------+
            | F7 | F8 | F9 | F10| F11| F12| INS|PSCR|
       +--------------------------------------------|
       | DEL| 7  | 8  | 9  | 0  | -  | =  |  BCKSPC | 
       +--------------------------------------------|
          | y  | u  | i  | o  | p  | [  | ]  |   \  |
      +---------------------------------------------|
      |PGUP| h  | j  | k  | l  | ;  | '  |    ENTER |
    +-----------------------------------------------|
    |HOME|PGDN| n  | m  | ,  | .  | /  |      SHIFT |
  +-------------------------------------------------+
  | END|   SPACE   | ALT | <- | ↓  | ↑  | -> | CTRL |
  +-------------------------------------------------+ */

/* /!\: rows are reversed in this half because I did all pcb design drunk */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_END, KC_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_RCTRL,
        KC_HOME, KC_PGDN, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSHIFT,
        KC_PGUP, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENTER,
        KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_DEL, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_PSCR
    )
};
