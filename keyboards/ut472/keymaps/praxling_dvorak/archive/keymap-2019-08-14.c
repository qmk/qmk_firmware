/* Copyright 2018 Carlos Filoteo
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

#define LT3_TAB LT(3, KC_TAB)
#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)
#define KC_LOCK RGUI(KC_L)

enum custom_keycodes {
    TOG_OS = SAFE_RANGE,

    // shortcuts
    UC_COPY,
    UC_PASTE,
    UC_CUT,
    UC_UNDO,
    KC_COMMENT,

    // media
    KC_MUTING,
    KC_VUP,
    KC_VDOWN
};

bool is_mac = true;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Base Layer
	* ,-------------------------------------------------------------------------.
	* | Esc |  ;  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |Bspace |
	* |-------------------------------------------------------------------------+
	* |Tab/L3|  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |   -  |
	* |-------------------------------------------------------------------------+
	* | Shift |  '  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  |Sh/En|
	* |-------------------------------------------------------------------------+
	* | Ctrl| Alt | App | Gui |  L2  |   Space   |  L1  | Left| Down|  Up |Right|
	* `-------------------------------------------------------------------------'
	*/
	[0] = LAYOUT(
        KC_ESC, KC_SCLN, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, 
        LT3_TAB, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, 
        KC_LSFT, KC_QUOT, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, MT_RSFT_ENT, 
        KC_LCTL, KC_LALT, KC_APP, KC_LGUI, MO(2), KC_SPC, MO(1), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),



	/* FN Layer 1
	* ,-------------------------------------------------------------------------.
	* |     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | Delete|
	* |-------------------------------------------------------------------------+
	* | Capsl | F1  | F2  | F3  | F4 |     |Gui+L|Gui+/|  @  |  !  |  ?  |  /   |
	* |-------------------------------------------------------------------------+
	* |       | F5  | F6  | F7  | F8 |     |     | Copy |Paste| Cut | Undo |    |
	* |-------------------------------------------------------------------------+
	* |     |     |     |     |      |          |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/
	[1] = LAYOUT(
        KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, 
        KC_CAPS, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_LOCK, KC_COMMENT, KC_AT, KC_EXLM, KC_QUES, KC_PSLS, 
        KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO, UC_COPY, UC_PASTE, UC_CUT, UC_UNDO, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END),



	/* FN Layer 2
	* ,-------------------------------------------------------------------------.
	* |      |  %  |  &  |  #  |  ~  |     |     |  $  |  |  |  `  |     |Delete|
	* |-------------------------------------------------------------------------+
	* | Capsl |  [  |  {  |  (  |  =  |     |     |  ^  |  )  |  }  |  ]  |  \  |
	* |-------------------------------------------------------------------------+
	* |  F9  | F10 | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19  | F20 |
	* |-------------------------------------------------------------------------+
	* |     |     |     |     |      |          |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/
	[2] = LAYOUT(
        KC_NO, KC_PERC, KC_AMPR, KC_HASH, KC_TILD, KC_NO, KC_NO, KC_DLR, KC_PIPE, KC_GRV, KC_NO, KC_DEL, 
        KC_CAPS, KC_LBRC, KC_LCBR, KC_LPRN, KC_EQL, KC_NO, KC_NO, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, 
        KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END),



	/* FN Layer 3
	* ,-------------------------------------------------------------------------.
	* | Esc |  :  |  =  |  +  |  -  |     |     |  7  |  8  |   9  |     |Bspace|
	* |-------------------------------------------------------------------------+
	* |      | Play | Prv | Next |    |    |  .  |  4  |  5  |  6  |   *  |  /  |
	* |-------------------------------------------------------------------------+
	* |       | Mute |Vol -|Vol +|     |    |  0  |  1  |  2  |  3  |Mous1|Mous2|
	* |-------------------------------------------------------------------------+
	* |TOG_OS|LEDtg|LED+|LED-|      |           |       |MousL|MousD|MousU|MousR|
	* `-------------------------------------------------------------------------'
	*/
	[3] = LAYOUT(
		KC_TRNS, KC_COLN, KC_EQL, KC_PPLS, KC_PMNS, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_NO, KC_BSPC, 
		KC_TRNS, KC_MPLY, KC_MRWD, KC_MFFD, KC_NO, KC_NO, KC_PDOT, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PSLS, 
		KC_TRNS, KC_MUTING, KC_VDOWN, KC_VUP, KC_NO, KC_NO, KC_P0, KC_P1, KC_P2, KC_P3, KC_BTN1, KC_BTN2, 
		TOG_OS, RGB_TOG, RGB_RMOD, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R)
};



//Custom functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
	  case TOG_OS:
      	is_mac = ! is_mac;
      	return false;

      case UC_COPY:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("c"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("c"));
      	}
      	return false;

      case UC_PASTE:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("v"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("v"));
      	}
      	return false;

      case UC_CUT:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("x"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("x"));
      	}
      	return false;

      case UC_UNDO:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("z"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("z"));
      	}
      	return false;

      case KC_COMMENT:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("/"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("/"));
      	}
      	return false;

      case KC_MUTING:
      	if (is_mac) {
      		SEND_STRING(SS_TAP(X__MUTE));
      	}
      	else {
      		tap_code(KC_MUTE);
      	}
      	return false;

      case KC_VUP:
      	if (is_mac) {
      		SEND_STRING(SS_TAP(X__VOLUP));
      	}
      	else {
      		tap_code(KC_VOLU);
      	}
      	return false;

      case KC_VDOWN:
      	if (is_mac) {
      		SEND_STRING(SS_TAP(X__VOLDOWN));
      	}
      	else {
      		tap_code(KC_VOLD);
      	}
      	return false;
      }
    }
    return true;
};