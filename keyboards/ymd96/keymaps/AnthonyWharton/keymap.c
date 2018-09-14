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

#define ______ KC_TRNS
#define _DEFLT 0
#define _RAISE 1

// Custom keymap for ISO Style Layout. Refer to the image in the README for
// an image of the full layout
#define KEYMAP( \
	K0500, K0502, K0503, K0504, K0505, K0600, K0610, K0710, K0700, K0511, K0512, K0513, K0514, K0113, K0214, K0013, K0706, K0709, K0708, \
	K0400, K0401, K0402, K0403, K0404, K0405, K0601, K0611, K0711, K0701, K0410, K0411, K0412,     K0414,    K0406, K0407, K0408, K0409, \
	  K0300,  K0301, K0302, K0303, K0304, K0305, K0602, K0612, K0712, K0702, K0310, K0311, K0312,   K0213,   K0306, K0307, K0308, K0309, \
	    K0200,   K0201, K0202, K0203, K0204, K0205, K0603, K0613, K0713, K0703, K0210, K0211, K0212,         K0206, K0207, K0208, K0209, \
	  K0100,  K0003, K0101, K0102, K0103, K0104, K0105, K0604, K0614, K0714, K0704, K0110,   K0111,   K0608, K0106, K0107, K0108, K0009, \
	  K0000,  K0001,  K0002,                 K0605,                          K0705,   K0011,   K0606, K0607, K0609, K0006, K0008         \
) { \
	{ K0000, K0001, K0002, K0003, KC_NO, KC_NO, K0006, KC_NO, K0008, K0009, KC_NO, K0011, KC_NO, K0013, KC_NO, }, \
	{ K0100, K0101, K0102, K0103, K0104, K0105, K0106, K0107, K0108, KC_NO, K0110, K0111, KC_NO, K0113, KC_NO, }, \
	{ K0200, K0201, K0202, K0203, K0204, K0205, K0206, K0207, K0208, K0209, K0210, K0211, K0212, K0213, K0214, }, \
	{ K0300, K0301, K0302, K0303, K0304, K0305, K0306, K0307, K0308, K0309, K0310, K0311, K0312, KC_NO, KC_NO, }, \
	{ K0400, K0401, K0402, K0403, K0404, K0405, K0406, K0407, K0408, K0409, K0410, K0411, K0412, KC_NO, K0414, }, \
	{ K0500, KC_NO, K0502, K0503, K0504, K0505, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0511, K0512, K0513, K0514, }, \
	{ K0600, K0601, K0602, K0603, K0604, K0605, K0606, K0607, K0608, K0609, K0610, K0611, K0612, K0613, K0614, }, \
	{ K0700, K0701, K0702, K0703, K0704, K0705, K0706, KC_NO, K0708, K0709, K0710, K0711, K0712, K0713, K0714  }  \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	/* Layer 0, default layer */	
	[_DEFLT] = KEYMAP(
		KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_HOME, KC_END,  KC_INS,  KC_DEL,  KC_PGUP, \
		KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,      KC_BSPC,      KC_LNUM, KC_PSLS, KC_PAST, KC_PGDN, \
		KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_ENT,     KC_P7,   KC_P8,   KC_P9,   KC_PMNS, \
		KC_LCAP,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,                   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
		KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,    KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
		KC_LCTL,  KC_LGUI, KC_LALT,                              KC_SPC,                        MO(_RAISE),      KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT           \
	),

	/* Layer 1, raise layer */ 
	[_RAISE] = KEYMAP(
		______,   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,   KC_F24,  ______,  KC_PAUS, KC_SLCK, ______,  ______,  ______,   \
		______,   RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, BL_OFF,  BL_ON,   BL_DEC,   BL_INC,       ______,      ______,  ______,  ______,  ______,   \
		______,   ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  RGB_VAD,  RGB_VAI,      KC_MUTE,     ______,  KC_VOLU, ______,  ______,   \
		______,   ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  RGB_TOG,  BL_TOGG,                   KC_MPRV, KC_MPLY, KC_MNXT, ______,   \
		______,   ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,  ______,        ______,      KC_PGUP, ______,  KC_VOLD, ______,  KC_LOCK,  \
		______,   ______,  KC_RALT,                               ______,                            ______,       ______,     KC_HOME, KC_PGDN, KC_END,  ______,  ______             \
	)
};
