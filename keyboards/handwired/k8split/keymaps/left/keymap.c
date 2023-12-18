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

#define KC_AUDIO_MMUTE KC_F20
#define KC_COMP KC_APP

/* LEFT
   +---------------------------------------+
   | ESC| F1 | F2 | F3 | F4 | F5 | F6 |MUTE|
   +---------------------------------------|
   | `  | 1  | 2  | 3  | 4  | 5  | 6  |MMIC| 
   +-----------------------------------------+
   | TAB  | q  | w  | e  | r  | t  | JP | MWU|
   +------------------------------------------+
   | CTRL  | a  | s  | d  | f  | g  |COMP| MWD|
   +---------------------------------------------|
   | SHIFT    | z  | x  | c  | v  | b  | F13| F14|
   +-------------------------------------------------+
   | CTRL |CAPS|SUPR| ALT |   SPACE   | F15| F16| F17|
   +-------------------------------------------------+ */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_AUDIO_MUTE,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_AUDIO_MMUTE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_INT5, KC_MS_WH_UP,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_COMP, KC_MS_WH_DOWN,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_F13, KC_F14,
        KC_LCTL, KC_CAPS, KC_LWIN, KC_LALT, KC_SPC, KC_F15, KC_F16, KC_F17
    )
};
