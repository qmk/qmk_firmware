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

	make rgbkb/sol3/rev1:fsargent:flash
	*/

#include QMK_KEYBOARD_H

enum layers { BASE, WIN, GAME, SYM, NAV, WINNAV, SHFT, MEH};

bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

#include "encoder.c"
#include "oled.c"
#include "rgb.c"
#include "combos.c"


// The very important timer.
void matrix_scan_user(void) {
  if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 500) {
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Tab size 4

	[BASE] = LAYOUT(
		KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,								KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
		KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,								KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_EQL,
	LT(MEH,KC_ESC),	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,								KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,		KC_QUOT,
		KC_LSFT,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,	ENCODER_MODE,			TO(WIN),	KC_N,		KC_M,		KC_COMM,		KC_DOT,		KC_SLSH,		MT(MOD_LSFT,KC_BSLS),
		MT(MOD_LCTL, KC_LBRC),	MT(MOD_LALT, KC_RBRC),	LT(SYM,KC_DEL), MO(NAV),	CMD_T(KC_BSPC),		KC_SPC,		LT(SYM, KC_ENT),	MT(MOD_RGUI, KC_DEL),	MT(MOD_RALT, KC_MINS), 	MT(MOD_RCTL, KC_EQL)
	),
	// [CMK] = LAYOUT(
	// 	KC_GRV,			KC_1,	KC_2,	KC_3,	KC_4,	KC_5,									KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
	// 	LT(SYM,KC_TAB),		KC_Q,	KC_W,	KC_F,	KC_P,	KC_B,									KC_J,		KC_L,		KC_U,		KC_Y,		KC_SCLN,	KC_BSLS,
	// 	MT(MOD_MEH,KC_ESC),	KC_A,	KC_R,	KC_S,	KC_T,	KC_G,									KC_M,		KC_N,		KC_E,		KC_I,		KC_O,		KC_QUOT,
	// 	KC_LSFT,	s	KC_Z,	KC_X,	KC_C,	KC_D,	KC_V,	_______,			TO(WIN),	KC_K,		KC_H,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_BSLS),
	// 	_______,	_______,	_______,	_______,	_______,						_______,	_______,	_______,	_______,	_______
	// ),
	[WIN] = LAYOUT(
		_______,	_______,	_______,	_______,	_______,	_______,							_______,_______,_______,_______,_______,_______,
		_______,	_______,	_______,	_______,	_______,	_______,							_______,_______,_______,_______,_______,_______,
LT(MEH,KC_ESC),	_______,	_______,	_______,	_______,	_______,						_______,_______,_______,_______,_______,_______,
		_______,	_______,	_______,	_______,	_______,	_______,	_______,	TO(GAME),	_______,_______,_______,_______,_______,_______,
		_______,	_______,	_______,	MO(WINNAV),	CTL_T(KC_BSPC),							_______,_______,_______,_______,_______
	),
	[GAME] = LAYOUT(
		KC_GRV,		_______,	_______,	_______,	_______,	_______,							_______,_______,_______,_______,_______,KC_BSPC,
		KC_TAB,		_______,	_______,	_______,	_______,	_______,							_______,_______,_______,_______,_______,_______,
		KC_ESC,		_______,	_______,	_______,	_______,	_______,							_______,_______,_______,_______,_______,_______,
		KC_LSFT,	_______,	_______,	_______,	_______,	_______,	_______,	TO(SHFT),	_______,_______,_______,_______,_______,_______,
		MO(WINNAV),	MO(SYM),	KC_LALT,	KC_LCTL,	KC_SPC,								KC_SPC, LT(SYM, WINNAV),_______,MT(MOD_LALT, KC_LBRC),	MT(MOD_LCTL, KC_RBRC)
	),
	[SHFT] = LAYOUT(
		KC_GRV,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,								KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		MT(MOD_LGUI,KC_MINS),
		KC_TAB,		KC_T,		KC_Q,		KC_W,		KC_E,		KC_R,								KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		MT(MOD_LCTL,KC_EQL),
LT(MEH,KC_ESC),		KC_G,		KC_A,		KC_S,		KC_D,		KC_F,								KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	MT(MOD_LALT,KC_QUOT),
		KC_LSFT,	KC_B,		KC_Z,		KC_X,		KC_C,		KC_V,	_______,		TO(BASE),	KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_BSLS),
		MT(MOD_LCTL, KC_LBRC),	MT(MOD_LALT, KC_RBRC),	LT(SYM,KC_DEL), KC_LCTL,	KC_SPC,				KC_BSPC,	LT(SYM, KC_ENT),	_______,_______,_______
	),
	[SYM] = LAYOUT(
		// C(G(KC_SPC)) is the OS X Emoji Editor
		C(G(KC_SPC)),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,							KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,
		_______,		KC_EQL,		KC_7,		KC_8,		KC_9,		KC_MINUS,						KC_NO,		KC_LPRN,	KC_LBRC,	KC_RBRC,	KC_RPRN,	KC_F12,
		_______,		KC_0, 		KC_4,		KC_5,		KC_6,		KC_PLUS,						KC_NO,		KC_LT,		KC_LCBR,	KC_RCBR,	KC_GT,		KC_NLCK,
		_______,		KC_DOT,		KC_1,		KC_2,		KC_3,		KC_ENT,	_______,		KC_NO,	KC_NLCK,	KC_SLCK,	KC_LT,	 	KC_GT,		KC_NO,		KC_SLCK,
		_______,		KC_0,		KC_NO,		_______,	_______,							_______,_______,	_______,	_______,	_______
	),
	[NAV]=LAYOUT(
		C(KC_GRV),	KC_NO,		G(KC_UP),	KC_PGUP,	A(KC_UP),	KC_NO,							KC_APP,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_LPRN,	KC_RPRN,
		C(KC_TAB),	A(KC_BSPC),	A(KC_LEFT),	KC_UP,		A(KC_RGHT),	A(KC_DEL),						KC_WH_L,	KC_WH_U,	KC_MS_U,	KC_WH_R,	KC_LBRC,	KC_RBRC,
		KC_MEH,		G(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	G(KC_RGHT),						KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_LCBR,	KC_RCBR,
		KC_LSFT,	KC_HOME,	G(KC_DOWN),	KC_PGDN,	A(KC_DOWN),	KC_END,		_______,	KC_NO,	KC_WH_D,	KC_WH_D,	KC_LCBR,	KC_RCBR,	KC_LT,		KC_GT,
		_______,	_______,	_______,	_______,	_______,							KC_BTN1,KC_BTN2,	_______,	_______,	_______
	),
	[WINNAV]=LAYOUT(
		C(KC_GRV),	TO(WIN),	C(KC_UP),	KC_PGUP,	A(KC_UP),	KC_NO,								KC_APP,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_LPRN,	KC_RPRN,
		ALT_TAB,	C(KC_BSPC),	C(KC_LEFT),	KC_UP,		C(KC_RGHT),	C(KC_DEL),							KC_WH_L,	KC_WH_U,	KC_MS_U,	KC_WH_R,	KC_LBRC,	KC_RBRC,
		KC_LGUI,	KC_HOME,	KC_LEFT,	KC_DOWN,	KC_RGHT,	KC_END,								KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_LCBR,	KC_RCBR,
		KC_LSFT,	KC_HOME,	C(KC_DOWN),	KC_PGDN,	A(KC_DOWN),	KC_END,	_______,			KC_NO,	KC_WH_D,	KC_WH_D,	KC_LCBR,	KC_RCBR,	KC_LT,		KC_GT,
		_______,	_______,	_______,	_______,	_______,								KC_BTN1,KC_BTN2,	_______,	_______,	_______
	),
	[MEH]=LAYOUT(
		_______,	MEH(KC_1),	MEH(KC_2),	MEH(KC_3),	MEH(KC_4),	MEH(KC_5),								_______,	_______,	_______,	_______,	_______,	_______,
		_______,	MEH(KC_Q),	MEH(KC_W),	MEH(KC_E),	MEH(KC_R),	MEH(KC_T),								_______,	_______,	_______,	_______,	_______,	_______,
		_______,	MEH(KC_A),	MEH(KC_S),	MEH(KC_D),	MEH(KC_F),	MEH(KC_G),								_______,	_______,	_______,	_______,	_______,	_______,
		_______,	MEH(KC_Z),	MEH(KC_X),	MEH(KC_C),	MEH(KC_V),	MEH(KC_B),	_______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,
								_______,	_______,	_______,	KC_ENT, 	KC_SPC,			_______,	_______,	_______,	_______,	_______
	),
};
