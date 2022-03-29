/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,either version 2 of the License,or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not,	see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "combos.c"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_split_4x6_5(
	KC_GRV,			KC_1,			KC_2,			KC_3,		KC_4,		KC_5,				KC_6,			KC_7,		KC_8,		KC_9,		KC_0,			KC_MINS,
	KC_TAB,			KC_Q,			KC_W,			KC_E,		KC_R,		KC_T,				KC_Y,			KC_U,		KC_I,		KC_O,		KC_P,			KC_EQL,
MT(MOD_MEH,KC_ESC),	KC_A,			KC_S,			KC_D,		KC_F,		KC_G,				KC_H,			KC_J,		KC_K,		KC_L,		KC_P,			KC_QUOT,
	KC_LSFT,		LT(3,KC_Z),		KC_X,			KC_C,		KC_V,		KC_B,				KC_N,			KC_M,		KC_COMM,	KC_DOT,		LT(3,KC_SLSH),	MT(MOD_LSFT,KC_BSLS),
									LT(2,KC_DEL),	CMD_T(KC_BSPC),			MO(1),				LT(2, KC_ENT),	KC_NO,		KC_SPC,
									MT(MOD_LCTL, KC_LBRC),	MT(MOD_LALT, KC_RBRC),				KC_NO,			KC_DEL
	),

	[1] = LAYOUT_split_4x6_5(
	C(KC_GRV),		KC_NO,			KC_NO,		KC_NO,		KC_NO,		KC_NO,					KC_CIRC,		KC_AMPR,	KC_ASTR,	KC_LPRN,	KC_RPRN,	KC_DEL,
	C(KC_TAB),		S(C(KC_TAB)),	A(KC_BSPC),	KC_UP,		A(KC_DEL),	C(KC_TAB),				KC_RBRC,		KC_P7,		KC_P8,		KC_P9,		_______,	KC_PLUS,
	KC_LCTRL,		A(KC_LEFT),		KC_LEFT,	KC_DOWN,	KC_RGHT,	A(KC_RGHT),				KC_RPRN,		KC_P4,		KC_P5,		KC_P6,		KC_MINS,	KC_PIPE,
	KC_LSFT,		KC_HOME,		G(KC_LEFT),	KC_ENT,		G(KC_RGHT),	KC_END,					_______,		KC_P1,		KC_P2,		KC_P3,		KC_EQL,		KC_UNDS,
												KC_LCTL,	KC_HOME,	KC_TRNS,				KC_TRNS,		KC_RALT,	KC_RGUI,
															KC_SPC,		KC_BSPC,				KC_RCTL,		KC_ENT
	),

	[2] = LAYOUT_split_4x6_5(
	C(G(KC_SPC)),	KC_F1,			KC_F2,		KC_F3,		KC_F4,		KC_F5,					KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,
	_______,		KC_EQL,			KC_7,		KC_8,		KC_9,		KC_MINUS,				KC_RBRC,	_______,	KC_NLCK,	KC_INS,		KC_SLCK,	KC_MUTE,
	_______,		KC_0,			KC_4,		KC_5,		KC_6,		KC_PLUS,				KC_RPRN,	KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_SCLN,	KC_SCLN,
	_______,		KC_DOT,			KC_1,		KC_2,		KC_3,		KC_ENT,					_______,	_______,	_______,	_______,	_______,	KC_VOLD,
												KC_LCTL,	KC_HOME,	KC_TRNS,				KC_TRNS,	KC_RALT,	RESET,
															KC_SPC,		KC_BSPC,			KC_RCTL,	KC_ENT
	),

	[3] = LAYOUT_split_4x6_5(
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,_______,
//---------------------------------------------------------//--------------------------------------------------------------//
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
								KC_BTN2,	KC_BTN1,	KC_BTN3,			KC_BTN3,	KC_BTN1,	KC_BTN2,
										KC_SPC,	KC_BSPC,			KC_RCTL,	KC_ENT
	),
};
