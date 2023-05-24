/*
Copyright 2011,2012,2015 Jun Wako <wakojun@gmail.com>
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

--------------

Ported to QMK by Techsock <info@techsock.com>
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Default:
	 * M0110                                                       M0120
	 * ,---------------------------------------------------------. ,---------------.
	 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \| |  7|  8|  9|  -|
	 * |---------------------------------------------------------| |---------------|
	 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift   | |  1|  2|  3|   |
	 * `---------------------------------------------------------' |-----------|Ent|
	 *      |Opt|Mac |         Space               |Fn  |Opt|      |      0|  .|   |
	 *      `-----------------------------------------------'      `---------------'
	 * M0110A
	 * ,---------------------------------------------------------. ,---------------.
	 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
	 * |-----------------------------------------------------'   | |---------------|
	 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shft|Up | |  1|  2|  3|   |
	 * |---------------------------------------------------------| |-----------|Ent|
	 * |Opt  |Mac    |         Space             |  \|Lft|Rgt|Dn | |      0|  .|   |
	 * `---------------------------------------------------------' `---------------'
	 */

	[0] = LAYOUT_ansi(
	       KC_GRV,  KC_1,    KC_2, KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8,    KC_9,   KC_0,             KC_MINS, KC_EQL,  KC_BSPC,  KC_NLCK, KC_EQL, KC_PSLS, KC_PAST,
	       KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,   KC_P,             KC_LBRC, KC_RBRC,           KC_P7,   KC_P8,  KC_P9,   KC_PMNS,
	       KC_LCAP, KC_A,    KC_S, KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,          KC_QUOT,          KC_ENT,   KC_P4,   KC_P5,  KC_P6,   KC_PPLS,
	       KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,                            KC_UP,    KC_P1,   KC_P2,  KC_P3,   KC_PENT,
	       KC_LALT, KC_LGUI,                   KC_SPC,                      MO(1),  LT(1, KC_BSLASH), KC_LEFT, KC_RGHT, KC_DOWN,  KC_P0,           KC_PDOT),
		
	
	/* Cursor Layer:
	 * M0110                                                       M0120
	 * ,---------------------------------------------------------. ,---------------.
	 * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |Hom| Up|PgU|Rst|   |   |   |Psc|Slk|Pau|Up |INS|   | |  7|  8|  9|  -|
	 * |---------------------------------------------------------| |---------------|
	 * |Ctrl  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Shift   |End|   |PgD|   |   |   |   |End|PgD|Dow|Shift   | |  1|  2|  3|   |
	 * `---------------------------------------------------------' |-----------|Ent|
	 *      |Opt|Mac |         Space               |Fn  |Opt|      |      0|  .|   |
	 *      `-----------------------------------------------'      `---------------'
	 * M0110A
	 * ,---------------------------------------------------------. ,---------------.
	 * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |INS|   | |  7|  8|  9|  -|
	 * |-----------------------------------------------------'   | |---------------|
	 * |Caps  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Ctrl    |End|   |PgD|   |   |   |   |End|PgD|Dow|Shft|PgU| |  1|  2|  3|   |
	 * |---------------------------------------------------------| |-----------|Ent|
	 * |Opt  |Mac    |         Space             |  \|Hom|End|PgD| |      0|  .|   |
	 * `---------------------------------------------------------' `---------------'
	 */
	
	[1] = LAYOUT_ansi(
	       KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_DEL,   KC_NLCK, KC_EQL, KC_PSLS, KC_PAST,
		   KC_TAB,  KC_HOME, KC_UP,   KC_PGUP, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,   KC_INS,           KC_P7,   KC_P8,  KC_P9,   KC_PMNS,
		   KC_LCAP, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,         KC_ENT,   KC_P4,   KC_P5,  KC_P6,   KC_PPLS,
		   KC_LCTL, KC_END,  KC_NO,   KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO, KC_END,  KC_PGDN, KC_DOWN,                  KC_PGUP,  KC_P1,   KC_P2,  KC_P3,   KC_PENT,
	       KC_LALT, KC_LGUI,                          KC_SPC,                       KC_TRNS, KC_TRNS, KC_HOME, KC_END, KC_PGDN,  KC_P0,           KC_PDOT),

};