/*
Copyright 2016 Julien Pecqueur <julien@peclu.net>
Copyright 2016 Felix Uhl <ifreilicht@gmail.com>

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

#define KC_MO1 MO(1)
#define KC_SPFN LT(1, KC_SPC)
#define KC_SDEL S(KC_DEL)
#define KC_CINS C(KC_INS)
#define KC_SINS S(KC_INS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Layout 0: Default Layer
	* ,-----------------------------------------------------------.
	* |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
	* |-----------------------------------------------------------|
	* |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
	* |-----------------------------------------------------------|
	* |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
	* |-----------------------------------------------------------|
	* |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
	* |-----------------------------------------------------------|
	* |Fn1 |Gui |Alt |        SpaceFn         |Alt |Gui |App |Ctrl|
	* `-----------------------------------------------------------'
	*/
    LAYOUT_kc(
		GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS,  EQL, BSPC, BSPC, \
		TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, BSLS, \
		LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN,    QUOT, NUHS, ENT,  \
		LSFT, NUBS, Z,    X,    C,    V,    B,    N,    M, COMM,  DOT,    SLSH,   NO, RSFT, NO, \
		MO1,  LGUI, LALT,             SPFN,                         RALT, RGUI, APP,  RCTL),

	/* Layout 1: Function Layer
	* ,-----------------------------------------------------------.
	* |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
	* |-----------------------------------------------------------|
	* |     |Prv|Ply|Nxt|Stp|   |   |PUp|Up |PDn|   |Slk|Pau|Ins  |
	* |-----------------------------------------------------------|
	* |      |Vl-|Mut|Vl+|   |   |Hom|Lef|Dow|Rig|End|   |PEnt    |
	* |-----------------------------------------------------------|
	* |        |Prt|Cut|Cop|Pst|Cal|   |   |   |   |   |CapsLock  |
	* |-----------------------------------------------------------|
	* |    |    |    |                        |    |    |    |    |
	* `-----------------------------------------------------------'
	*/
    LAYOUT_kc(
		ESC,  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,  TRNS, DEL,  \
		TRNS, MPRV, MPLY, MNXT, MSTP, TRNS, TRNS, PGUP, UP,   PGDN, TRNS, SLCK, PAUS, INS,  \
		TRNS, VOLD, MUTE, VOLU, TRNS, TRNS, HOME, LEFT, DOWN, RGHT, END,  TRNS, TRNS, PENT, \
		TRNS, TRNS, PSCR, SDEL, CINS, SINS, CALC, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, CAPS, TRNS, \
		TRNS, TRNS, TRNS,             TRNS,                         TRNS, TRNS, TRNS, TRNS),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
