/*pteron56
*Copyright (C) 2023 @kraken-jokes
*
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*IMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "pteron56.h"
enum my_keycodes {
	PASS = SAFE_RANGE,
	USER 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL,
		KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
		PASS, KC_CAPS, KC_SPC, KC_ENT, TG(1), KC_SPC, KC_RALT, KC_RGUI),

	LAYOUT(
		LCTL(KC_X), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_PSLS, KC_PAST, KC_INS, KC_BSPC, 
		KC_TAB, KC_LBRC, KC_UP, KC_RBRC, KC_LCBR, KC_RCBR, KC_NLCK, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_DEL, 
		LCTL(KC_V), KC_LEFT, KC_DOWN, KC_RGHT, LCTL(KC_Z), LCTL(KC_TAB), KC_PGUP, KC_P4, KC_P5, KC_P6, KC_PMNS, TO(2), 
		LCTL(KC_C), LALT(KC_F4), LALT(KC_ESC), KC_MUTE, KC_MSTP, KC_MPLY, KC_PGDN, KC_P1, KC_P2, KC_P3, KC_BSLS, TO(0), 
		KC_TRNS, KC_LCTL, KC_LSFT, KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0 ),

	LAYOUT(
		RESET, KC_SLEP, KC_WAKE, KC_TRNS, KC_PWR, KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS, KC_BSPC, 
		KC_GRV, KC_WBAK, KC_WFWD, KC_WSCH, KC_FIND, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PSLS, KC_PAST, 
		KC_DEL, KC_CALC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4, KC_P5, KC_P6, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_LBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_PDOT, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, LGUI(LSFT(KC_S)), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case PASS:
		if (record->event.pressed) {
			// when keycode M4 is pressed	
			SEND_STRING("Ineedmorethan24h)@");
		} else {
			// when keycode M4 is released
		}
		break;
	case USER:
		if(record->event.pressed) {
			// when keycode USER is pressed
			SEND_STRING("lahlouh211");
		} else {
			// when keycode USER is released
		}
		break;
	}
	return true;
}
