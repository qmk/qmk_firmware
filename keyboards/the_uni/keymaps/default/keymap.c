/*
Copyright 2021 Peter C. Park <peter@stenokeyboards.com>

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
#include "keymap_steno.h"

enum uni_layers {
/*
  _QWERTY,
  _CHOOSE,
*/
  _PLOVER,
};

/*
enum uni_keycodes {
	PLOVER,
	QWERTY
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
	 [_QWERTY] = LAYOUT(
	 	KC_Q, KC_W, KC_E, KC_R, LT(_CHOOSE, KC_T), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, 
	 	KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
	 	            KC_1, KC_C, KC_V, KC_N, KC_M, KC_2),

	 [_CHOOSE] = LAYOUT(
	 	_______, _______, _______, _______, _______, PLOVER, _______, _______, _______, _______, _______, 
	 	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
	 	            _______, _______, _______, _______, _______, _______),
*/
	[_PLOVER] = LAYOUT(
		STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,  STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR , 
		STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,  STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR , 
		                  STN_N1,  STN_A,   STN_O,    STN_E,    STN_U,   STN_N2),

};

/*
switch (keycode) {
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 	case PLOVER:
       if (!record->event.pressed) {
		 layer_on(_PLOVER);
       }
       return false;
       break;
 	case QWERTY:
       if (!record->event.pressed) {
		 layer_on(_QWERTY);
       }
       return false;
       break;
 	}
 	return true;
 }
*/

 void matrix_init_user() {
   steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
 }
