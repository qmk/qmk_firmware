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

// Planck keycodes needed for dynamic macros
enum planck_keycodes {

  QWERTY = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,

};

// Tap Dance
enum {

  SFT_CAPS = 0,

};

#include "dynamic_macro.h"

#define MOUSE_LAYER 2

const uint16_t PROGMEM fn_actions[] = {

  [2] = ACTION_LAYER_TOGGLE(MOUSE_LAYER),

};

qk_tap_dance_action_t tap_dance_actions[] = {

  [SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  KEYMAP(
	 M(0), M(1), M(2), M(3), M(4), DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, 
	 KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
	 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, 
	 CTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, 
	 TD(SFT_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SFT_T(KC_ENT), 
	 MO(2), MO(1), KC_LGUI, KC_RALT, KC_LCTRL, KC_SPC, ALT_T(KC_LEFT), ALL_T(KC_RGHT), LT(1, KC_UP), LT(2, KC_DOWN)),
  
  KEYMAP(
	 M(7), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DYN_REC_START1, DYN_REC_START2, 
	 DYN_REC_STOP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_LBRC, KC_P7, KC_P8, KC_P9, KC_ASTR, KC_DEL, 
	 KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_RBRC, KC_P4, KC_P5, KC_P6, KC_PLUS, KC_EQL, 
	 KC_BSLS, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_LCBR, KC_P1, KC_P2, KC_P3, KC_MINS, KC_PIPE, 
	 KC_TRNS, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_RCBR, KC_P0, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  
  KEYMAP(
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
	 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, F(2))
};

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
