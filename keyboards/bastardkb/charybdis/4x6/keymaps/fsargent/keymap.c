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

	[0] = LAYOUT(
	KC_GRV,			KC_1,		KC_2,		KC_3,		KC_4,			KC_5,					KC_6,		KC_7,		KC_8,		KC_9,		KC_0,			KC_MINS,
	KC_TAB,			KC_Q,		KC_W,		KC_E,		KC_R,			KC_T,					KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,			KC_BSLS,
	MT(MOD_MEH,KC_ESC),	LGUI_T(KC_A),	LALT_T(KC_S),	LCTL_T(KC_D),	LSFT_T(KC_F),		LT(3,KC_G),				KC_H,		LSFT_T(KC_J),	LCTL_T(KC_K),	LALT_T(KC_L),	LGUI_T(KC_QUOT),	KC_QUOT,
	KC_LSFT,		LT(3,KC_Z),	LT(3,KC_X),	LT(3,KC_C),	LT(3,KC_V),		KC_B,					KC_N,		KC_M,		KC_COMM,	KC_DOT,		LT(3,KC_SLSH),		MT(MOD_LSFT,KC_BSLS),
								MO(1),		CMD_T(KC_BSPC),		LT(2,KC_TAB),				LT(2, KC_ENT),	LT(2, KC_SPC),
								MT(MOD_LCTL, KC_LBRC),			MT(MOD_LALT, KC_RBRC),			KC_DEL
	),

	[1] = LAYOUT(
	C(KC_GRV),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,					KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_DEL,
	C(KC_TAB),	A(KC_BSPC),	A(KC_LEFT),	KC_UP,		A(KC_RGHT),	A(KC_DEL),				KC_PERC,	KC_P7,		KC_P8,		KC_P9,		KC_COLN,	KC_K,
	_______,	G(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	G(KC_RGHT),				KC_PPLS,	KC_P4,		KC_P5,		KC_P6,		KC_MINS,	KC_PEQL,
	_______,	KC_HOME,	G(KC_DOWN),	KC_DEL,		G(KC_UP),	KC_END,					KC_PAST,	KC_P1,		KC_P2,		KC_P3,		KC_PSLS,	S(KC_G),
							KC_LCTL,	KC_HOME,	KC_TRNS,				KC_PDOT,	KC_KP_0,
									KC_SPC,		KC_BSPC,				KC_ENT
	),

	[2] = LAYOUT(
	KC_GRV,		KC_GRV,		KC_LPRN,	KC_RPRN,	KC_SCLN,	KC_COMM,		_______,	_______,	_______,	_______,	_______,	KC_BSPC,
	KC_EXLM,	KC_LCBR,	KC_QUOT,	KC_DQT,		KC_RCBR,	KC_QUES,		KC_SCLN,	KC_LSFT,	KC_LCTL,	KC_LALT,	KC_LGUI,	_______,
	KC_HASH,	KC_CIRC,	KC_EQL,		KC_UNDS,	KC_DLR,		KC_ASTR,		KC_DOT,		LSFT_T(KC_BSPC),LCTL_T(KC_TAB),	LALT_T(KC_SPC),	LGUI_T(KC_ENT),	_______,
	KC_TILD,	KC_LT,		KC_PIPE,	KC_MINS,	KC_GT,		KC_SLSH,		KC_SLSH,	KC_DEL,		S(KC_TAB),	_______,	_______,	_______,
							KC_LCTL,	KC_LPRN,	KC_RPRN,		KC_TRNS,	_______,
									KC_LBRC,	KC_RBRC,		KC_ENT
	),

	[3] = LAYOUT(
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
	_______,	DRAGSCROLL_MODE,	DRAGSCROLL_MODE,	DRAGSCROLL_MODE,	DRAGSCROLL_MODE,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
//---------------------------------------------------------//--------------------------------------------------------------//
								KC_BTN2,	KC_BTN1,	KC_BTN3,			KC_BTN2,	KC_BTN1,
										KC_SPC,	KC_BSPC,				KC_ENT
	),

	[4]	= LAYOUT(
	KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,						KC_CIRC,	KC_HASH,	KC_DLR,		KC_TILD,	KC_EXLM,	KC_NUM,
	_______,	KC_PAST,	KC_P7,		KC_P8,		KC_P9,		KC_MINS,					KC_PERC,	KC_P7,		KC_P8,		KC_P9,		KC_COLN,	KC_K,
	KC_NUM,		KC_KP_0,	KC_P4,		KC_P5,		KC_P6,		KC_PPLS,					KC_PPLS,	KC_P4,		KC_P5,		KC_P6,		KC_MINS,	KC_PEQL,
	_______,	KC_PSLS,	KC_P1,		KC_P2,		KC_P3,		KC_EQL,						KC_PAST,	KC_P1,		KC_P2,		KC_P3,		KC_PSLS,	S(KC_G),
							_______,	KC_KP_0,	_______,					KC_PDOT,	KC_KP_0,
								KC_KP_0,	KC_LPRN,						KC_ENT
	)
};
