/*
Copyright 2021 id-b3
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

#define _____________________COLEMAK_L1_____________________ KC_ESC,        KC_Q, KC_W, KC_F, KC_P, KC_G
#define _____________________COLEMAK_L2_____________________ KC_DEL,        KC_A, KC_R, KC_S, KC_T, KC_D
#define _____________________COLEMAK_L3_____________________ OSL(0), CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B
#define _____________________THUMBS_LF1_____________________ TO(0), KC_DOWN, MT(MOD_LSFT, KC_SPC), LT(0, KC_ENT), KC_UP
#define _____________________THUMBS_LF2_____________________ OSM(MOD_LSFT), KC_DOWN

#define _____________________COLEMAK_R1_____________________ KC_J, KC_L, KC_U   , KC_Y  , KC_SCLN        , KC_NONUS_BSLASH
#define _____________________COLEMAK_R2_____________________ KC_H, KC_N, KC_E   , KC_I  , KC_O           , CMD_T(KC_QUOTE)
#define _____________________COLEMAK_R3_____________________ KC_K, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLASH), OSL(_SHORTCUT)
#define _____________________THUMBS_RG1_____________________ TO(_QWERTY), TD(TD_TABC), KC_BSPC, KC_LEFT, KC_RGHT
#define _____________________THUMBS_RG2_____________________ OSL(_NAVIGATION), C(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
      KC_ESC,        KC_Q, KC_W, KC_F, KC_P, KC_G,       KC_J, KC_L, KC_U   , KC_Y  , KC_SCLN        , KC_NONUS_BSLASH,
      KC_DEL,        KC_A, KC_R, KC_S, KC_T, KC_D,       KC_H, KC_N, KC_E   , KC_I  , KC_O           , CMD_T(KC_QUOTE),
      OSL(0), CTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,	      KC_K, KC_M, KC_COMM, KC_DOT, CTL_T(KC_SLASH), OSL(0),
      TO(0), KC_DOWN, MT(MOD_LSFT, KC_SPC), LT(0, KC_ENT), KC_UP,       TO(0), KC_TAB, KC_BSPC, KC_LEFT, KC_RGHT,
	  OSM(MOD_LSFT), KC_DOWN,       OSL(0), C(KC_TAB)
    )
	
	/*[_BLANK] = LAYOUT(
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,	       _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
	  _______,                                                                                                  _______
    )
	*/

};
