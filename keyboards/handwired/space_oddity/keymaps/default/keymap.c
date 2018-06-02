/*  Keymap for Space Oddity Keyboard
    Copyright (C) 2017  James Taylor

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "space_oddity.h"

// Planck keycodes needed for dynamic macros.
enum planck_keycodes {

  QWERTY = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,

};

// Tap Dance initializer.
enum {

  SFT_CAPS = 0,

};

#include "dynamic_macro.h"

#define MOUSE_LAYER 2

// Toggle MOUSE_LAYER. Additional layers can be added for additional layouts or other special functions.
const uint16_t PROGMEM fn_actions[] = {

  [2] = ACTION_LAYER_TOGGLE(MOUSE_LAYER),

};

// Tap dance actions - double tap for Caps Lock.
qk_tap_dance_action_t tap_dance_actions[] = {

  [SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*      Here is an ASCII version of the base layout. Note that Dynamic Macros 1 and 2 are considered Macro 5 and Macro 6.
    
          ___________________________________________________________________________________
	 |           |           |           |           |           |  Dynamic  |  Dynamic  |
	 |  Macro 0  |  Macro 1  |  Macro 2  |  Macro 3  |  Macro 4  |  Macro 1  |  Macro 2  |                                      
	 |___________|___________|___________|___________|___________|___________|___________|
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |     `     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |   BKSP    |
	 |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |    TAB    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |     -     |
         |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |ESC (CTL_T)|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |     '     |
	 |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	   |         |     |     |     |     |     |     |     |     |     |     |         |
	   |  SHFT   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |SHFT(ENT)|
	   |_________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_________|
	       |     |     |     |     |           |           | ALT | HYP | LT 1| LT 2|
	       | M2  | M1  | GUI | ALT |    CTRL   |    SPC    |(LFT)|(RGT)| (UP)|(DWN)|
	       |_____|_____|_____|_____|___________|___________|_____|_____|_____|_____|
  */
  
  KEYMAP(
	 M(0), M(1), M(2), M(3), M(4), DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, 
	 KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
	 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, 
	 CTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
	 TD(SFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SFT_T(KC_ENT), 
	 MO(2), MO(1), KC_LGUI, KC_RALT, KC_LCTRL, KC_SPC, ALT_T(KC_LEFT), ALL_T(KC_RGHT), LT(1, KC_UP), LT(2, KC_DOWN)),

  /*     Function layer.
         Blank keys correspond to the KC_TRNS keycode.

          ___________________________________________________________________________________
	 |           |           |           |           |           |  DYN REC  |  DYN REC  |
	 |  Macro 7  |           |           |           |           |     1     |     2     |                                      
	 |___________|___________|___________|___________|___________|___________|___________|
	 |  DYN REC  |     |     |     |     |     |     |     |     |     |     |           |
	 |   STOP    | F1  | F2  | F3  | F4  | F5  |  [  |  7  |  8  |  9  |  *  |    DEL    |
	 |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |           | F6  | F7  | F8  | F9  | F10 |  ]  |  4  |  5  |  6  |  +  |     =     |
         |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |     \     | F11 | F12 | F13 | F14 | F15 |  {  |  1  |  2  |  3  |  -  |     |     |
	 |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	   |         |     |     |     |     |     |     |     |     |     |     |         |
	   |         | F16 | F17 | F18 | F19 | F20 |  }  |  0  |  ,  |  .  |  /  |         |
	   |_________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_________|
	       |     |     |     |     |           |           |     |     |     |     |
	       |     |     |     |     |           |           |     |     |     |     |
	       |_____|_____|_____|_____|___________|___________|_____|_____|_____|_____|

   */
  
  KEYMAP(
	 M(7), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DYN_REC_START1, DYN_REC_START2, 
	 DYN_REC_STOP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_LBRC, KC_P7, KC_P8, KC_P9, KC_ASTR, KC_DEL, 
	 KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_RBRC, KC_P4, KC_P5, KC_P6, KC_PLUS, KC_EQL, 
	 KC_BSLS, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_LCBR, KC_P1, KC_P2, KC_P3, KC_MINS, KC_PIPE, 
	 KC_TRNS, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_RCBR, KC_P0, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  /*     Mouse layer.

          ___________________________________________________________________________________
	 |           |           |           |           |           |           |           |
	 |           |           |           |           |           |           |           |                                      
	 |___________|___________|___________|___________|___________|___________|___________|
	 |           |     |     | MS  |     |     |     |     |     |     |     |           |
	 |           |     |     | UP  |     |     |     |     |     |     |     |           |
	 |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	 |           |     | MS  | MS  | MS  |     |     |     |     |     |     |           |
	 |           |     | LFT | DWN | RGT |     |     | MS1 | MS3 | MS2 |     |           |
         |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |           |     |     |     |     |     |     |     |     |     |     |           |
	 |___________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|___________|
	   |         |     |     |     |     |     |     |     |     |     |     |         |
	   |         |RESET|     |     |     |     |     |     |     |     |     |         |
	   |_________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_________|
	       |     |     |     |     |           |           |     |     |     |     |
	       |     |     |     |     |           |           |     |     |     | F(2)|
	       |_____|_____|_____|_____|___________|___________|_____|_____|_____|_____|

   */
  
  KEYMAP(
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, F(2))
};

// Simple macro ideas follow. Each of them is designed to give you a quick way to create pairs of
// delimiters and then position the cursor between them, much like Emacs' ParEdit does. This way,
// you can have some convenient coding "helpers" even when not using Emacs. It is also nice for
// LaTeX editing.
//
// Customize to your heart's content!
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  switch (id) {
  case 0:
    if (record->event.pressed) {
      SEND_STRING("()"SS_TAP(X_LEFT));
    }
    break;
    
  case 1:
    if (record->event.pressed) {
      SEND_STRING("[]"SS_TAP(X_LEFT));
    }
    break;
    
  case 2:
    if (record->event.pressed) {
      SEND_STRING("{}"SS_TAP(X_LEFT));
    }
    break;

    // Probably something only Lisp users will appreciate...  
  case 7:
    if (record->event.pressed) {
      SEND_STRING("(lambda ())"SS_TAP(X_LEFT)SS_TAP(X_LEFT));
    }
    break;
  }

  return MACRO_NONE;
  
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}
