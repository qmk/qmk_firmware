/* Copyright 2022 Sinan Okman (@simchee)
 *
 *  This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
	QWERTZ,
	LOWER,
	RAISE,
	FN1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[QWERTZ] = LAYOUT_planck_mit
	(
	 KC_TAB,		KC_Q,				KC_W,				KC_E,				KC_R,				KC_T,				KC_Z,				KC_U,				KC_I,				KC_O,				KC_P,				KC_BSPC,
	 MO(FN1),		KC_A,				KC_S,				KC_D,				KC_F,				KC_G,				KC_H,				KC_J,				KC_K,				KC_L,				KC_SCLN,		KC_SLSH,
	 KC_LSFT,		KC_Y,				KC_X,				KC_C,				KC_V,				KC_B,				KC_N,				KC_M,				KC_COMM,		KC_DOT,			KC_UP,			KC_ENT,
	 KC_ESC,		KC_LGUI,		KC_LCTL,		KC_LALT,		MO(LOWER),				KC_SPC,						MO(RAISE),	KC_ALGR,		KC_LEFT,		KC_DOWN,		KC_RIGHT
	 ),

	[LOWER] = LAYOUT_planck_mit
	(
	 KC_TAB,		KC_PGUP,		KC_UP,			KC_PGDN,		KC_HOME,		_______,		_______,		KC_7,				KC_8,				KC_9,				KC_EQL,			KC_BSPC,
	 MO(FN1),		KC_LEFT,		KC_DOWN,		KC_RIGHT,		KC_END,			_______,		KC_NUHS,		KC_4,				KC_5,				KC_6,				KC_ASTR,		KC_SLSH,
	 KC_LSFT,		KC_MUTE,		KC_VOLD,		KC_VOLU,		KC_MPLY,		KC_MPRV,		KC_MNXT,		KC_1,				KC_2,				KC_3,				KC_PLUS,		KC_ENTER,
	 KC_ESC,		RGB_TOG,		KC_LCTL,		KC_LALT,		MO(LOWER),				KC_SPC,						KC_COMM,		KC_0,				KC_DOT,			KC_MINS,		_______
	 ),

	[RAISE] = LAYOUT_planck_mit
	(
	 KC_CIRC,		KC_EXLM,		KC_AT,			_______,		KC_DLR,			KC_PERC,		KC_AMPR,		KC_ASTR,		KC_LPRN,		KC_RPRN,		KC_QUES,		KC_TILD,
	 MO(FN1),		_______,		_______,		_______,		_______,		_______,		_______,		KC_GRV,			KC_LBRC,		KC_RBRC,		KC_QUOT,		KC_BSLS,
	 KC_LSFT,		KC_MINS,		_______,		_______,		_______,		_______,		_______,		_______,		KC_LABK,		KC_RABK,		KC_EQL,			KC_HASH,
	 _______,		_______,		_______,		_______,		MO(LOWER),				KC_SPC, 					MO(RAISE),	KC_ALGR,		_______,		_______,		_______
	 ),
	
	[FN1] = LAYOUT_planck_mit
	(
	 KC_F12,		KC_F1,			KC_F2,			KC_F3,			KC_F4,			KC_F5,			KC_F6,			KC_F7,			KC_F8,			KC_F9,			KC_F10,			KC_DEL,
	 MO(FN1),		KC_F11,			_______,		_______,		_______,		_______,		KC_HOME,		KC_PGDN,		KC_PGUP,		KC_END,			_______,		_______,
	 KC_LSFT,		KC_CAPS,		_______,		_______,		_______,		_______,		KC_LEFT,		KC_DOWN,		KC_UP,			KC_RIGHT,		_______,		KC_APP,
	 QK_BOOT,		_______,		_______,		_______,		MO(LOWER),				KC_SPC,							KC_BSPC,	_______,		_______,		KC_PSCR,		KC_INS
	 )

};

