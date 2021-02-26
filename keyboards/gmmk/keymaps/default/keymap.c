/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/*
         ESC	F1	F2	F3	F4	F5	F6	F7	F8	F9	F10	F11	F12	  Prt	 Rotary(Mute)
         ~	1	2	3	4	5	6	7	8	9	0	 -	(=)	   BackSpc	 Del
         Tab	Q	W	E	R	T	Y	U	I	O	P	[	]	\	     PgUp
         Caps	A	S	D	F	G	H	J	K	L	;	"		 Enter	 PgDn
         Sh_L	Z	X	C	V	B	N	M	,	.	?	Sh_R		Up	 End
         Ct_L	Win_L	Alt_L	SPACE		  Alt_R	FN	Ct_R  Left	Down Right
*/


[0] = LAYOUT_gmmk_pro(
    KC_LSFT,   KC_MUTE,  _______,  KC_LEFT,    KC_RCTL,     KC_RGHT,    KC_LCTL,   KC_F5,    KC_R,   KC_T,      KC_F,     KC_G,       KC_V,     KC_B,    KC_5,    KC_4,      KC_P,  KC_LBRC,  KC_SCLN,  KC_QUOT,   _______,   KC_SLSH,  KC_MINS,    KC_0,
    KC_Q,      KC_TAB,   KC_A,      KC_ESC,       KC_Z,     KC_PGUP,     KC_GRV,    KC_1,    KC_U,   KC_Y,      KC_J,     KC_H,       KC_M,     KC_N,    KC_6,    KC_7,   KC_LWIN,  KC_RSFT,   KC_APP,  KC_LOPT,    KC_SPC,   KC_RALT,  _______, KC_PSCR,
    KC_W,      KC_LCAP,  KC_S,       KC_RO,       KC_X,     KC_PGDN,      KC_F1,    KC_2,    KC_I,   KC_RBRC,   KC_K,    KC_F6,    KC_COMM,   KC_DEL,  KC_EQL,    KC_8,   _______,  KC_BSPC,  KC_PIPE,   KC_F11,    KC_ENT,    KC_F12,    KC_F9,  KC_F10,
    KC_E,      KC_F3,    KC_D,       KC_F4,       KC_C,       KC_UP,      KC_F2,    KC_3,    KC_O,   KC_F7,     KC_L,  KC_DOWN,     KC_DOT,   KC_END,   KC_F8,    KC_9
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {return true;}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
}

void dip_switch_update_user(uint8_t index, bool active) {}

void matrix_scan_user(void) {}
