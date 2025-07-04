/* Copyright 2019 Mike Hix
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
			KC_GRV,   KC_1,     KC_2,     KC_3,        KC_4,        KC_5,            KC_HOME,         KC_END,          KC_6,            KC_7,        KC_8,        KC_9,       KC_0,     KC_EQL,
			KC_TAB,   KC_QUOT,  KC_COMM,  KC_DOT,      KC_P,        KC_Y,            KC_BSPC,         KC_DEL,          KC_F,            KC_G,        KC_C,        KC_R,       KC_L,     KC_BSLS,
			KC_ESC,   KC_A,     KC_O,     LT(1,KC_E),  LT(2,KC_U),  KC_I,            LCTL_T(KC_ENT),  RCTL_T(KC_ENT),  KC_D,            LT(3,KC_H),  LT(4,KC_T),  KC_N,       KC_S,     KC_MINS,
			KC_LSFT,  KC_SCLN,  KC_Q,     KC_J,        KC_K,        KC_X,            KC_PGUP,         KC_PGDN,         KC_B,            KC_M,        KC_W,        KC_V,       KC_Z,     KC_RSFT,
			KC_CAPS,  KC_INS,   KC_LCTL,  /*,          */KC_LALT,   LGUI_T(KC_SPC),  KC_HYPR,         KC_HYPR,         RGUI_T(KC_SPC),  KC_RALT,     /*,          */KC_LBRC,  KC_RBRC,  KC_SLSH
			),
	[1] = LAYOUT(
			XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  MS_WHLU,  XXXXXXX,  XXXXXXX,  QK_BOOT,
			XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_VOLU,  MS_WHLL,  MS_UP,    MS_WHLR,  XXXXXXX,  EE_CLR,
			XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  _______,  _______,  KC_MUTE,  MS_LEFT,  MS_DOWN,  MS_RGHT,  MS_BTN1,  MS_BTN2,
			_______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  KC_VOLD,  XXXXXXX,  MS_WHLD,  XXXXXXX,  MS_BTN3,  MS_BTN4,
			XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,  XXXXXXX,  XXXXXXX
			),
	[2] = LAYOUT(
			XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PGUP,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_INS,   KC_PSCR,  KC_UP,    KC_PAUS,  XXXXXXX,  XXXXXXX,
			XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  _______,  _______,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,   XXXXXXX,
			_______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  KC_PGDN,  XXXXXXX,  XXXXXXX,  _______,
			XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,  XXXXXXX,  XXXXXXX
			),
	[3] = LAYOUT(
			XXXXXXX,  KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			XXXXXXX,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			_______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
			XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,  XXXXXXX,  XXXXXXX
			),
	[4] = LAYOUT(
			QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			EE_CLR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			XXXXXXX,  UG_HUEU,  UG_SATU,  UG_VALU,  UG_NEXT,   UG_TOGG,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
			_______,  UG_HUED,  UG_SATD,  UG_VALD,  UG_PREV,   XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
			XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,   _______,  _______,  _______,  _______,  _______,            XXXXXXX,  XXXXXXX,  XXXXXXX
			)
	/*
	[] = LAYOUT(
		    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
		    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
		    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
		    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,
		    XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,  XXXXXXX,  XXXXXXX
		    )
    */	
};

