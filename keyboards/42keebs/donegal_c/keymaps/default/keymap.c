/* Copyright 2018 Yiancar
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
https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_br_abnt2.h
 https://github.com/qmk/qmk_firmware/issues/6325 SEE HERE IF COMPILE FAILS
*/
//#include QMK_KEYBOARD_H
#include "donegal_c.h"
#include "keymap_br_abnt2.h"
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	LAYOUT_60_abnt(
		KC_Z, KC_2, KC_3, KC_5, KC_7, KC_9, KC_MINS, KC_BSPC, 
		KC_CAPS, KC_1, KC_4, KC_6, KC_8, KC_0, KC_EQL, KC_BSPC, 
		KC_TAB, KC_Q, KC_E, KC_T, KC_U, KC_O, BR_ACUT, BR_LBRC, 
		BR_QUOT, KC_W, KC_R, KC_Y, KC_I, KC_P, KC_SCLN, KC_ENT, 
		KC_LSFT, KC_A, KC_D, KC_G, KC_J, KC_L, BR_TILD, BR_BSLS, 
		BR_RBRC, KC_S, KC_F, KC_H, KC_K, KC_COMM, BR_SCLN, BR_CCDL, 
		KC_LCTL, KC_X, KC_C, KC_B, KC_N, KC_DOT, KC_RGUI, KC_RCTL, 
		KC_LGUI, KC_LALT, KC_V, KC_SPC, KC_M, KC_RALT, KC_MENU, KC_RSFT),

	LAYOUT_60_abnt(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}
