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
// #include "rgb.c"
#include "combos.c"

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE, CMD_TAB, SELWORD

};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// 	switch (keycode) { // This will do most of the grunt work with the keycodes.

// //   case SELWORD:  // Selects the current word under the cursor.
// //     if (record->event.pressed) {
// //       // SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(ffdfd))));
// //       // Mac users, change LCTL to LALT:
// //       SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
// //     }
// //     break;
// 	case ALT_TAB:
// 		if (record->event.pressed) {
// 			if (!is_alt_tab_active) {
// 			is_alt_tab_active = true;
// 			register_code(KC_LALT);
// 			}
// 			alt_tab_timer = timer_read();
// 			register_code(KC_TAB);
// 		} else {
// 			unregister_code(KC_TAB);
// 		}
// 		break;
// 	case CMD_TAB:
// 		if (record->event.pressed) {
// 			if (!is_cmd_tab_active) {
// 			is_cmd_tab_active = true;
// 			register_code(KC_LGUI);
// 			}
// 			cmd_tab_timer = timer_read();
// 			register_code(KC_TAB);
// 		} else {
// 			unregister_code(KC_TAB);
// 		}
// 		break;
// 	}
//   return true;
// }

// void matrix_scan_user(void) { // The very important timer.
//   if (is_alt_tab_active) {
// 	if (timer_elapsed(alt_tab_timer) > 750) {
// 	  unregister_code(KC_LALT);
// 	  is_alt_tab_active = false;
// 	}
//   }
//   if (is_cmd_tab_active) {
// 	if (timer_elapsed(cmd_tab_timer) > 750) {
// 	  unregister_code(KC_LGUI);
// 	  is_cmd_tab_active = false;
// 	}
//   }
// }

enum layers { BASE, WIN, GAME, SYM, NAV, WINNAV};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Tab size 4

	[BASE] = LAYOUT(
		KC_GRV,			KC_1,	KC_2,	KC_3,	KC_4,	KC_5,							KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,
		KC_TAB,			KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,							KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_EQL,
		MT(MOD_MEH,KC_ESC),	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,							KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,
		KC_LSFT,		KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	C(G(KC_SPC)),			TO(WIN),	KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	MT(MOD_LSFT,KC_BSLS),
		MT(MOD_LCTL, KC_LBRC),	MT(MOD_LALT, KC_RBRC),	LT(SYM,KC_DEL), MO(NAV),	CMD_T(KC_BSPC),	KC_SPC,		KC_ENT,	MT(MOD_LSFT, KC_DEL),	MT(MOD_LALT, KC_MINS), 	MT(MOD_LCTL, KC_EQL)
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
		_______,_______,_______,_______,_______,_______,KC_LGUI,			TO(GAME),_______,_______,_______,_______,_______,_______,
		_______,_______,_______,MO(WINNAV),	CTL_T(KC_BSPC),				_______,_______,_______,_______,_______
	),
	[GAME] = LAYOUT(
		KC_GRV,		_______,	_______,	_______,	_______,	_______,				_______,_______,_______,_______,_______,_______,
		KC_TAB,		_______,	_______,	_______,	_______,	_______,				_______,_______,_______,_______,_______,_______,
		LT(SYM,KC_ESC),	_______,	_______,	_______,	_______,	_______,				_______,_______,_______,_______,_______,_______,
		KC_LSFT,	_______,	_______,	_______,	_______,	_______,MO(SYM),	TO(BASE),	_______,_______,_______,_______,_______,_______,
		KC_LCTL,	KC_LALT,	MO(NAV),	KC_LCTL,	KC_BSPC,				KC_SPC,		LT(NAV, KC_ENT),	MT(MOD_LGUI,KC_DEL),	KC_LBRC,	KC_RBRC
	),
	[SYM]	=	LAYOUT(
		// C(G(KC_SPC)) is the OS X Emoji Editor
		C(G(KC_SPC)),	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,							KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,
		_______,	KC_GRV,		KC_NO,		KC_NO,		KC_NO,		KC_NO,							KC_INS,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_F12,
		_______,	KC_1,		KC_2,		KC_3,		KC_4,		KC_5,							KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_PSCR,
		_______,	KC_NO,		KC_LCBR, 	KC_RCBR,	KC_NO,		KC_NO,	C(G(KC_SPC)),			TG(SYM),	KC_MINS,	KC_EQL,		KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_NLCK,
		_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______
),
	[NAV]=LAYOUT(
		C(KC_TAB),	G(KC_SLSH),	KC_NO,		KC_WH_U,	KC_WH_R,	G(KC_ENT),							KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MINS,	KC_EQL,		KC_EQL,
		S(C(KC_TAB)),	A(KC_BSPC),	KC_PGUP,	KC_UP,		KC_ENT,		A(KC_DEL),							KC_WH_L,	KC_WH_U,	KC_MS_U,	KC_WH_R,	KC_WH_R,		KC_RBRC,
		C(KC_TAB),	A(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	A(KC_RGHT),							KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_SCLN,	KC_LGUI,
		MT(MOD_LSFT,KC_TAB),	KC_HOME,	G(KC_LEFT),	SELWORD,	G(KC_RGHT),		KC_END,	G(KC_ENT),		TO(GAME),	KC_WH_D,	KC_WH_D,	KC_LCBR,	KC_RCBR,	KC_BSLS,	KC_DEL,
		_______,	_______,	_______,	_______,	_______,							KC_BTN1,	KC_BTN2,	KC_BTN3,	RGB_RMOD,	RGB_MOD
	),
	[WINNAV]=LAYOUT(
		C(KC_GRV),	MEH(2),		KC_NO,		KC_WH_U,	KC_WH_R,	G(KC_ENT),						KC_NO,		KC_MPRV,	KC_MPLY,	KC_MNXT,	KC_MUTE,	KC_EQL,
		KC_TAB, 	C(KC_BSPC),	KC_PGUP,	KC_UP,		KC_ENT,		C(KC_DEL),					KC_WH_U,	KC_WH_L,	KC_MS_U,	KC_WH_R,	KC_END,		KC_RBRC,
		KC_LGUI,	C(KC_LEFT),	KC_LEFT,	KC_DOWN,	KC_RGHT,	C(KC_RGHT),					KC_BTN3,	KC_MS_L,	KC_MS_D,	KC_MS_R,	KC_NO,		KC_LGUI,
		KC_LSFT,	KC_HOME,	KC_PGDN,	KC_SPC,		KC_SPC,		KC_END,		G(KC_ENT),	TG(GAME),	KC_WH_D,	KC_NO,		KC_LCBR,	KC_RCBR,	KC_BSLS,	KC_DEL,
		_______,	_______,	_______,	_______,	_______,							KC_BTN1,	KC_BTN2,	KC_BTN3,	KC_LBRC,	KC_RBRC
	)
};
