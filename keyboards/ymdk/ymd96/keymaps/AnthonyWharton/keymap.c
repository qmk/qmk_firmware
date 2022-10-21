/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Anthony Wharton <th3ant@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public LicensezZZ
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _DEFLT 0
#define _RAISE 1


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	/* Layer 0, default layer */	
	[_DEFLT] = LAYOUT_iso(
		KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_HOME, KC_END,  KC_INS,  KC_DEL,  KC_PGUP, \
		KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,      KC_BSPC,      KC_LNUM, KC_PSLS, KC_PAST, KC_PGDN, \
		KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_ENT,     KC_P7,   KC_P8,   KC_P9,   KC_PMNS, \
		KC_LCAP,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,                   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
		KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,    KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
		KC_LCTL,  KC_LGUI, KC_LALT,                              KC_SPC,                        MO(_RAISE),      KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT           \
	),

	/* Layer 1, raise layer */ 
	[_RAISE] = LAYOUT_iso(
		_______,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,   KC_F24,  _______, KC_PAUS, KC_SCRL, _______, _______, _______,  \
		_______,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, BL_OFF,  BL_ON,   BL_DEC,   BL_INC,       _______,     _______, _______, _______, _______,  \
		_______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD,  RGB_VAI,      KC_MUTE,     _______, KC_VOLU, _______, _______,  \
		_______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,  BL_TOGG,                   KC_MPRV, KC_MPLY, KC_MNXT, _______,  \
		_______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,     KC_PGUP, _______, KC_VOLD, _______, QK_LOCK,  \
		_______,  _______, KC_RALT,                               _______,                           _______,      _______,    KC_HOME, KC_PGDN, KC_END,  _______, _______            \
	)
};
