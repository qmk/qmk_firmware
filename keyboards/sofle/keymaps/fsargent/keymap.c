/* Copyright 2020 Josef Adamcik
	* Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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


#include "oled.c"
#include "encoder.c"
#include "rgb.c"
#include "combos.c"

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE, CMD_TAB, SELWORD
};

enum layers { BASE, WIN, GAME, SYM, NAV, WINNAV};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Tab size 4

	[BASE] = LAYOUT(
		KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,							KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
		KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,							KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_EQL,
	MT(MOD_MEH,KC_ESC),	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,							KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,
		KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,	C(G(KC_SPC)),			TO(WIN),	KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_BSLS),
				MT(MOD_LCTL, KC_LBRC),	MT(MOD_LALT, KC_RBRC),	LT(SYM,KC_DEL), MO(NAV), CMD_T(KC_BSPC),		KC_SPC,		LT(SYM, KC_ENT),	MT(MOD_LGUI, KC_DEL),	MT(MOD_LALT, KC_MINS), 	MT(MOD_LCTL, KC_EQL)
	),
	// [CMK] = LAYOUT(
	// 	KC_GRV,			KC_1,	KC_2,	KC_3,	KC_4,	KC_5,											KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
	// 	LT(SYM,KC_TAB),		KC_Q,	KC_W,	KC_F,	KC_P,	KC_B,											KC_J,		KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_BSLS,
	// 	MT(MOD_MEH,KC_ESC),	KC_A,	KC_R,	KC_S,	KC_T,	KC_G,											KC_M,		KC_N,		KC_E,		KC_I,		KC_O,		KC_QUOT,
	// 	KC_LSFT,			KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	_______,					TO(WIN),	KC_K,		KC_H,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_BSLS),
	// 	_______,	_______,	_______,	_______,	_______,								 _______,	_______,	_______,	_______,	_______
	// ),
	[WIN] = LAYOUT(
		_______,_______,_______,_______,_______,_______,					_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,					_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,					_______,_______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,_______,KC_LGUI,		TO(GAME),	_______,_______,_______,_______,_______,_______,
		_______,_______,_______,MO(WINNAV),	CTL_T(KC_BSPC),					_______,_______,_______,_______,_______
	),
	[GAME] = LAYOUT(
		KC_GRV,		_______,	_______,	_______,	_______,	_______,				_______,_______,_______,_______,_______,_______,
		KC_TAB,		_______,	_______,	_______,	_______,	_______,				_______,_______,_______,_______,_______,_______,
		KC_ESC,		_______,	_______,	_______,	_______,	_______,				_______,_______,_______,_______,_______,_______,
		KC_LSFT,	_______,	_______,	_______,	_______,	_______,MO(SYM),	TO(BASE),	_______,_______,_______,_______,_______,_______,
		KC_LCTL,	KC_LALT,	MO(WINNAV),	KC_LCTL,	KC_BSPC,						_______,_______,_______,_______,_______
	),
	[SYM]	=	LAYOUT(
		// C(G(KC_SPC)) is the OS X Emoji Editor
		C(G(KC_SPC)),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,							KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,
		_______,	KC_EQL,		KC_7,		KC_8,		KC_9,		KC_MINUS,						KC_INS,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_F12,
		_______,	KC_0, 		KC_4,		KC_5,		KC_6,		KC_PLUS,							KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_0,		KC_PSCR,
		_______,	KC_DOT,		KC_1,		KC_2,		KC_3,		KC_ENT,	C(G(KC_SPC)),		TG(SYM),	KC_MINS,	KC_EQL,		KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_NLCK,
						_______,	KC_0,		KC_NO,		_______,	_______,		_______,	_______,	_______,	_______,	_______
),
	[NAV]=LAYOUT(
		C(KC_GRV),	KC_HOME,	KC_PGUP,	KC_NO,		KC_PGDN,	KC_END,						KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MINS,	KC_EQL,		KC_EQL,
		C(KC_TAB),	S(C(KC_TAB)),	A(KC_BSPC),	KC_UP,		A(KC_DEL),	C(KC_TAB),							KC_WH_L,	KC_WH_U,	KC_MS_U,	KC_WH_R,	KC_WH_R,		KC_RBRC,
		KC_LCTRL,	A(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	A(KC_RGHT),						KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_SCLN,	KC_LGUI,
		KC_LSFT,	KC_HOME,	G(KC_LEFT),	KC_ENT,		G(KC_RGHT),	KC_END,		G(KC_ENT),		TO(GAME),	KC_WH_D,	KC_WH_D,	KC_LCBR,	KC_RCBR,	KC_BSLS,	KC_DEL,
		_______,	_______,	_______,	_______,	_______,								KC_BTN1,	KC_BTN2,	KC_BTN3,	RGB_RMOD,	RGB_MOD
	),
	[WINNAV]=LAYOUT(
		C(KC_GRV),	KC_HOME,	KC_PGUP,	KC_NO,		KC_PGDN,	KC_END,							KC_NO,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MUTE,	KC_EQL,
		A(KC_TAB), 	S(KC_TAB),	C(KC_BSPC),	KC_UP,		C(KC_DEL),	KC_TAB,							KC_WH_U,	KC_WH_L,	KC_MS_U,	KC_WH_R,	KC_END,		KC_RBRC,
		KC_LALT,	C(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	C(KC_RGHT),						KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_NO,		KC_LGUI,
		KC_LSFT,	KC_HOME,	A(KC_LEFT),	KC_ENT,		A(KC_RGHT),	KC_END,		G(KC_ENT),		TG(GAME),	KC_WH_D,	KC_NO,		KC_LCBR,	KC_RCBR,	KC_BSLS,	KC_DEL,
		_______,	_______,	_______,	_______,	_______,								KC_BTN1,	KC_BTN2,	KC_BTN3,	KC_LBRC,	KC_RBRC
	)
};
