/* Copyright 2020 Oliver Granlund
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

/* ISO 60 layout by olligranlund
*
* This layout starts from a standard ISO 60% layout, and adds one function layer.
* If you wish to only have one wide spacebar, you can easily do that by dismissing the "side" spacebar switches.
*
* Default Layer
* ,-----------------------------------------------------------------------------------------.
* | Esc | 1 ! | 2 " | 3 § | 4 $ | 5 % | 6 & | 7 / | 8 ( | 9 ) | 0 = | ß ? | ´ ` | Del | BSPC|
* |-----------------------------------------------------------------------------------------|
* | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  Ä  | + * | Enter  |
* |----------------------------------------------------------------------------------       |
* | FN      |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ü  | # ' |       |
* |-----------------------------------------------------------------------------------------|
* | Shift | < > |  Z  |  X  |  C  |  V  |  B  |  N  |  M  | , ; | . : | - _ |  Shift  |Shift|
* |-----------------------------------------------------------------------------------------|
* | LCtl  | LGUI  | LAlt  |  Space      | Space |  Space     | RAlt | FN | App | RCtl |     |
* `-----------------------------------------------------------------------------------------'
*/

enum custom_keycodes {
    EMOJI_DANCERS = SAFE_RANGE,
	EMOJI_PERJANTAI,
	EMOJI_THISISFINE,
	EMOJI_KOVAAAJOA,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
    	case EMOJI_DANCERS:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING(">dancers>");
			}
			break;

		case EMOJI_PERJANTAI:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING(">perjantaideploy>");
			}
			break;
		
		case EMOJI_THISISFINE:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING(">this/is/fine>");
			}
			break;
    
		case EMOJI_KOVAAAJOA:
			if (record->event.pressed) {
				// when keycode QMKBEST is pressed
				SEND_STRING(">kovaaajoa>");
			}
			break;
    }
    
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	// 0 Base
	LAYOUT_60_iso_5x1u_split_bs_rshift_spc(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
		MO(2),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, TG(1),
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(3),    KC_APP,  KC_PSCR, KC_RCTL),

	// 1 Base with arrows
	LAYOUT_60_iso_5x1u_split_bs_rshift_spc(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
		MO(2),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP, KC_TRNS,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, MO(3),    KC_LEFT,  KC_DOWN, KC_RGHT),

	// 2 FN
	LAYOUT_60_iso_5x1u_split_bs_rshift_spc(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_DEL,
		KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,   KC_NO,   KC_PGDN,  KC_UP,   KC_PGUP, KC_NO,   KC_NO,   KC_NO,
		KC_NO,   KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,   KC_NO,   KC_HOME, KC_LEFT,  KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_END,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT, KC_CAPS,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_NO,    KC_APP,  KC_PSCR, KC_RCTL),

	// 3 FN with RGB and macros
	LAYOUT_60_iso_5x1u_split_bs_rshift_spc(
		KC_GRV,  RGB_TOG,   		RGB_MOD,   		RGB_RMOD,   		RGB_HUI, RGB_SAI, RGB_VAI, RGB_HUD,  RGB_SAD, RGB_VAD, KC_F10,  KC_F11,  KC_F12,  KC_DEL,  QK_BOOT,
		KC_NO,   KC_NO, 			EMOJI_DANCERS, 	KC_NO, 				KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO,   EMOJI_PERJANTAI,   EMOJI_THISISFINE,EMOJI_KOVAAAJOA,	KC_NO,   KC_NO,   KC_NO,   KC_LEFT,  KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_LSFT, KC_NO, 			KC_NO, 			KC_NO, 				KC_NO,   KC_NO,   KC_NO,   KC_END,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_RSFT, KC_CAPS,
		KC_LCTL, KC_LGUI, 			KC_LALT,		KC_SPC,  			KC_SPC,  KC_SPC,  KC_RALT, KC_NO,    KC_APP,  KC_PSCR, KC_RCTL),
	
};
