/* Copyright 2022 Sandipratama <https://github.com/nendezkombet>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "encoder.h"

#define PLAY	    KC_MPLY
#define BKMARK      LCTL(KC_D)
#define REOPTAB     RCS(KC_T)
#define RELOAD      KC_F5
#define COPY        LCTL(KC_C)
#define PASTE       LCTL(KC_V)
#define SELECT      LCTL(KC_A)
#define SAVE        LCTL(KC_S)
#define NEWTAB      LCTL(KC_T)
#define SNIP        SWIN(KC_S)		//Snip and sketch

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
  		TO(1) , PLAY   , KC_MPRV,  KC_MNXT,
  		BKMARK, REOPTAB, NEWTAB ,  RELOAD,
  		SAVE  , KC_HOME, SNIP   ,  KC_DEL,
  		SELECT, COPY   , PASTE  ,  KC_ENT
	),
	[1] = LAYOUT(
		TO(2)  , RGB_TOG, RGB_RMOD, RGB_MOD,
		RGB_HUI, RGB_SAI, RGB_VAI,  RGB_M_B,
		RGB_HUD, RGB_SAD, RGB_VAD,  RGB_M_SW,
		KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
	),
	[2] = LAYOUT(
		TO(3)  , KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
};



bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
	    }
	}
    return true;
}



//qmk compile -kb antari -km via
