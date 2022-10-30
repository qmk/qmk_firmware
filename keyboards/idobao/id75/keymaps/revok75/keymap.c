/* Copyright 2017 Wunder
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

// Layer shorthand
#define _QW_M 0
#define _QW_W 1
#define _FN 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* QWERTY-Mac
	 * .--------------------------------------------------------------------------------------------------------------------------------------.
	 * | ESC    | 1      | 2      | 3      | 4      | %      | 6     | 7      | 8      | 9      | 0      | -       | =    | Cut    | BACKSP   |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
	 * | TAB    | Q      | W      | E      | R      | T      | Y     | U      | I      | O      | P      | {      | }     | Copy   | Paste    |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
	 * | CAP LK | A      | S      | D      | F      | G      | H     | J      | K      | L      | ;      | '      | ENTER  | ENTER | REF      |
	 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
	 * | LSHIFT | Z      | X      | C      | V      | B      | N     | M      | ,      | .      | /      | \      | RSHIFT| UP     | SAVE     |
	 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
	 * |  LALT   | LGUI   | LALT	|	FIND	| CMD T   | SPACE  | SPACE | ALFRED | FN-MO  | RALT   | RGUI   | RCTRL  | LEFT  | DOWN   | RIGHT    |
	 * '--------------------------------------------------------------------------------------------------------------------------------------'
	 */

	[_QW_M] = LAYOUT_ortho_5x15( /* QWERTY MAC*/
		KC_GESC,  KC_1,     KC_2,     KC_3,     	KC_4,     	KC_5, 	KC_6,   KC_7,   				KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,     LGUI(KC_X),  KC_BSPC, \
		KC_TAB,   KC_Q,     KC_W,     KC_E,     	KC_R,     	KC_T, 	KC_Y,   KC_U,   				KC_I,     KC_O,     KC_P,     KC_LCBR,    KC_RCBR,    LGUI(KC_C),  LGUI(KC_V), \
		KC_CAPS,  KC_A,     KC_S,     KC_D,     	KC_F,     	KC_G, 	KC_H,   KC_J,   				KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    LGUI(KC_R), KC_NO,       KC_ENT, \
		KC_LSFT,  KC_Z,     KC_X,     KC_C,     	KC_V,     	KC_B, 	KC_N,   KC_M,   				KC_COMM,  KC_DOT,   KC_SLSH,  KC_BSLS,    KC_RSFT,    KC_UP,       LGUI(KC_S), \
		KC_LCTL,  KC_LALT,  KC_LGUI,	LGUI(KC_F), LGUI(KC_T), KC_SPC, KC_NO, 	LALT(KC_SPACE),	MO(_FN), 	KC_RGUI,  KC_RALT,  KC_RCTL,    KC_LEFT,    KC_DOWN,     KC_RGHT \
	),

	 /* QWERTY-Win
	  * .--------------------------------------------------------------------------------------------------------------------------------------.
	  * | ESC    | 1      | 2      | 3      | 4      | %      | 6     | 7      | 8      | 9      | 0      | -       | =    | Cut    | BACKSP   |
	  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
	  * | TAB    | Q      | W      | E      | R      | T      | Y     | U      | I      | O      | P      | {      | }     | Copy   | Paste    |
	  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
	  * | CAP LK | A      | S      | D      | F      | G      | H     | J      | K      | L      | ;      | '      | ENTER  | ENTER | REF      |
	  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
	  * | LSHIFT | Z      | X      | C      | V      | B      | N     | M      | ,      | .      | /      | \      | RSHIFT | UP    | SAVE     |
	  * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
	  * | LALT   | LGUI   | LALT   |  FIND  | CMD T	 | SPACE | SPACE  | START  | FN-MO  | RALT   | RGUI   | RCTRL  | LEFT  | DOWN   | RIGHT    |
	  * '--------------------------------------------------------------------------------------------------------------------------------------'
	  */

  [_QW_W] = LAYOUT_ortho_5x15( /* QWERTY WIN*/
  	KC_GESC,  KC_1,     KC_2,     KC_3,     		KC_4,     	KC_5, 	KC_6,   KC_7,   				KC_8,     KC_9,     KC_0,     KC_MINS,     KC_EQL,     LCTL(KC_X),  KC_BSPC, \
  	KC_TAB,   KC_Q,     KC_W,     KC_E,     		KC_R,     	KC_T, 	KC_Y,   KC_U,   				KC_I,     KC_O,     KC_P,     KC_LCBR,     KC_RCBR,    LCTL(KC_C),  LCTL(KC_V), \
  	KC_CAPS,  KC_A,     KC_S,     KC_D,     		KC_F,     	KC_G, 	KC_H,   KC_J,   				KC_K,     KC_L,     KC_SCLN,  KC_QUOT,     LCTL(KC_R), KC_NO,       KC_ENT, \
  	KC_LSFT,  KC_Z,     KC_X,     KC_C,     		KC_V,     	KC_B, 	KC_N,   KC_M,   				KC_COMM,  KC_DOT,   KC_SLSH,  KC_BSLS,     KC_RSFT,    KC_UP,       LCTL(KC_S), \
  	KC_LCTL,  KC_LALT,  KC_LGUI,  LCTL(KC_F), 	LCTL(KC_T), KC_SPC, KC_NO,	LCTL(KC_GESC),	MO(_FN), 	KC_RGUI,  KC_RALT,  KC_RCTL,     KC_LEFT,    KC_DOWN,     KC_RGHT \
 	),

	/* FUNCTION
	* .--------------------------------------------------------------------------------------------------------------------------------------.
	* | ESC    | F1     | F2     | F3     | F4     | F5     | F6    | F7     | F8     | F9     | F10    | VOLDN   | VOLUP  | MUTE   | DEL    |
	* |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
	* | TAB    | -      | WIN    | -      | -      | RGB_TOG| -     | -      | OPTION  | QK_BOOT  | -      | [      | ]     | -       | -      |
	* |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
	* | CAP LK | MAC    | RAINBOW| PLAIN  | -      | -      | -     | -      | -      | -      | ;      | '       | ENTER |  ENTER  | REF    |
	* |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
	* | LSHIFT | INC    | DEC    | HUE I  | HUE D  | SAT I  | SAT D | -      | -      | .      | /       | \      | RSHIFT|  HOME   | SAVE   |
	* |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
	* | LALT   | LGUI   | LALT   |  FIND  | CMD T	 | SPACE | SPACE  | ALFRED | FN-MO  | RALT   | RGUI    | RCTRL  | PGUP   | END    | PGDN   |
	* '--------------------------------------------------------------------------------------------------------------------------------------'
	*/

 	[_FN] = LAYOUT_ortho_5x15( /* OSLAYOUT + NUMPAD + MEDIA + LIGHTING */
  	KC_TRNS, KC_F1,     KC_F2,						 KC_F3,    		   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_VOLD, KC_VOLU, KC_MUTE, KC_DEL, \
  	KC_TRNS, KC_NO,     DF(_QW_W),    		 KC_NO,    		   KC_NO,   RGB_TOG, KC_NO,   KC_NO,   KC_RALT, QK_BOOT, KC_NO,   KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, \
  	KC_TRNS, DF(_QW_M), RGB_MODE_RAINBOW,  RGB_MODE_PLAIN, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  	KC_TRNS, RGB_VAI,   RGB_VAD,  				 RGB_HUI,  		   RGB_HUD, RGB_SAI, RGB_SAD, KC_NO,   KC_NO,   KC_DOT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, \
  	KC_TRNS, KC_TRNS,   KC_TRNS,  				 KC_TRNS,  		   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_END,	 KC_PGDN \
	),
};
