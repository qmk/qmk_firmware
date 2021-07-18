/* Copyright 2021 Hanachi
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

enum custom_layers {
    _QWERTY,
    _FN1,
    _FN2,
    _FN3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QUWERTY Layer */
[_QWERTY] = LAYOUT(
/* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7-----| |--R1---+--R2---+--R3---+--R4---+--R5---+--R6---+--R7---+--R8---+---R9--+--R10-- | */
	KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,   KC_8,   KC_9,	KC_0,  KC_MINS, KC_EQL, KC_GRV, KC_BSPC,
	KC_TAB,	   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  KC_LBRC, KC_RBRC,KC_BSLS,
	KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,
	KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,  KC_DEL,  KC_LGUI, KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                KC_RSFT,
          LT(_FN1,KC_LEFT), ALT_T(KC_RIGHT), KC_SPC,  KC_LCTL, KC_ENT,  KC_BSPC, LT(_FN2, KC_DOWN),	LT(_FN3, KC_UP)
/* |-------+-------+-------+-------+-------+-------+---------| |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------| */
 ),

/*  NUM Pad layer */
[_FN1] = LAYOUT(
/* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7-----| |--R1---+--R2---+--R3---+--R4---+--R5---+--R6---+--R7---+--R8---+---R9--+--R10-- | */
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,				    KC_NLCK,XXXXXXX,XXXXXXX,KC_LPRN, KC_RPRN,_______,_______,_______,_______,
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,					KC_P7,	KC_P8,	KC_P9,	KC_MINUS,KC_EQL, _______,_______,_______,
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,					KC_P4,	KC_P5,	KC_P6,	KC_PLUS, KC_ASTR, KC_COMM,	     _______,
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,    KC_P0, KC_P1,	KC_P2,	KC_P3,	KC_DOT,	 KC_SLSH,				 _______,
					         _______,_______,_______,_______,	 _______,_______,_______,_______
/* |-------+-------+-------+-------+-------+-------+---------| |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------| */
),

/* Cursor key layer */
[_FN2] = LAYOUT(
/* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7-----| |--R1---+--R2---+--R3---+--R4---+--R5---+--R6---+--R7---+--R8---+---R9--+--R10-- | */
	_______, KC_F1,	 KC_F2,	 KC_F3,	 KC_F4,  KC_F5,					    KC_F6,	KC_F7,	KC_F8,	KC_F9,	 KC_F10,KC_F11,	 KC_F12, KC_INS, KC_PSCR,
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,					XXXXXXX,KC_PGDN,KC_UP,	KC_PGUP, XXXXXXX,XXXXXXX,XXXXXXX,_______,
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,				    XXXXXXX,KC_LEFT,KC_DOWN,KC_RIGHT,XXXXXXX,XXXXXXX,		 _______,
	_______, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,	XXXXXXX,XXXXXXX,KC_HOME,KC_DOWN,KC_END,  XXXXXXX,				 _______,
							_______, _______,_______,_______,    _______,_______,_______,_______
/* |-------+-------+-------+-------+-------+-------+---------| |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------| */
),

/* System layer */
[_FN3] = LAYOUT(
/* |--L1---+--L2---+--L3---+--L4---+--L5---+--L6---+--L7-----| |--R1---+--R2---+--R3---+--R4---+--R5---+--R6---+--R7---+--R8---+---R9--+--R10-- | */
	RESET,	RGB_TOG,RGB_MOD,RGB_RMOD,XXXXXXX,XXXXXXX,					XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
	XXXXXXX,XXXXXXX,RGB_VAD,RGB_VAI, XXXXXXX,XXXXXXX,					XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,		XXXXXXX,
	XXXXXXX,XXXXXXX,RGB_SAD,RGB_SAI, XXXXXXX,XXXXXXX,				    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,				XXXXXXX,
	XXXXXXX,XXXXXXX,RGB_HUD,RGB_HUI, XXXXXXX,XXXXXXX,XXXXXXX,   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,						XXXXXXX,
							_______,_______,_______,_______,	_______,_______,_______,_______
/* |-------+-------+-------+-------+-------+-------+---------| |--------+-------+-------+-------+-------+-------+-------+-------+-------+-------| */
)

};
