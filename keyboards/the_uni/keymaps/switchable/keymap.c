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
  _QWERTY = 0
  ,_GEMINI
  ,_LOWER
  ,_RAISE
  ,_CHOOSE
};

enum uni_keycodes {
	GEMINI = SAFE_RANGE
    ,QWERTY
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define CHOOSE MO(_CHOOSE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	 [_QWERTY] = LAYOUT(
	 	KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
	 	KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
	 	            RAISE, KC_C, KC_V, KC_N, KC_M, LOWER),

	[_GEMINI] = LAYOUT(
		STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,  STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
		STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,  STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
		                  RAISE,  STN_A,   STN_O,    STN_E,    STN_U,   LOWER),

	 [_RAISE] = LAYOUT(
	 	   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
	 	KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	 	            _______, KC_LCMD, KC_LALT, KC_SPC, KC_LCTRL, CHOOSE),

	 [_LOWER] = LAYOUT(
	 	KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
	 	KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	 	            CHOOSE, KC_LCTRL, KC_SPC, KC_LALT, KC_LCMD, _______),

	 [_CHOOSE] = LAYOUT(
	 	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	 	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	 	            _______, XXXXXXX, QWERTY, GEMINI, XXXXXXX, _______),
};


 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GEMINI:
            if (!record->event.pressed) {
                set_single_persistent_default_layer(_GEMINI);
            }
            return false;
        case QWERTY:
            if (!record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
        return false;
 	}
 	return true;
 }

 void matrix_init_user() {
   steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
 }

