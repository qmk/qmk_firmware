/* Copyright 2021 grezeh
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
enum layer_names {
    base,
    morf,
	fx,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[base] = LAYOUT(
		KC_ESC,  KC_C,    KC_T,    KC_O,    KC_H,    KC_PSCR, KC_K,    KC_W,    KC_U,    KC_R,  
		KC_BSPC, KC_S,    KC_A,    KC_E,    KC_I,    KC_DEL,  KC_P,    KC_L,    KC_J,    KC_F,             KC_ENT, 
		KC_PGUP, KC_LBRC, KC_COMM, KC_X,    KC_N,    KC_MINS, KC_EQL,  KC_M,    KC_Q,    KC_DOT,  KC_RBRC, KC_PGDN, 
		                  KC_HOME, KC_LCTL, KC_SPC,  KC_LSFT, MO(1),   MO(2),   KC_LALT, KC_END),

	[morf] = LAYOUT( 
		KC_TAB,  KC_SCLN, KC_D,    KC_PMNS, KC_PPLS, KC_NLCK, KC_G,    KC_SLSH, KC_GRV,  KC_QUOT, 
		KC_TRNS, KC_Z,    KC_PEQL, KC_PSLS, KC_PAST, KC_CAPS, KC_B,    KC_BSLS, KC_Y,    KC_V,             KC_TRNS, 
		KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS, 
		                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	[fx] = LAYOUT(
		KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9, 
		KC_MUTE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS, KC_PDOT, KC_AT,   KC_HASH, KC_TILD,          KC_TRNS, 
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, 
		                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};
