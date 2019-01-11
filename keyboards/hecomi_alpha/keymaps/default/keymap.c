/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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
#include "hecomi_alpha.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

//R1:7 8
//R2:7 8
//R3:6 7
//R4:6 8
//R5:6 6
//
enum layers{
	DF,
	FN
};

#define KC_FN MO(FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DF]=LAYOUT(\
			ESC,1,2,3,4,5,6,                  7,8,9,0,MINS,EQL,NUHS,GRV,\
			TAB  ,Q,W,E,R,T,Y,                 Y,U,I,O,P,LBRC,RBRC,BSPC,\
			LCTRL ,A,S,D,F,G,                     H,J,K,L,SCLN,QUOT,ENT,\
			LSFT   ,Z,X,C,V,B,               B,N,M,COMM,DOT,SLSH,RSFT,FN,\
			LCTRL,LGUI,LALT,MHEN,BSPC,SPC,  ENT,ESC,HENK,RALT,RGUI,RCTRL\
			),
	[FN]=LAYOUT(\
			ESC,1,2,3,4,5,6,                  7,8,9,0,MINS,EQL,NUHS,GRV,\
			TAB  ,Q,W,E,R,T,Y,                 Y,U,I,O,P,LBRC,RBRC,BSPC,\
			LCTRL ,A,S,D,F,G,                     H,J,K,L,SCLN,QUOT,ENT,\
			LSFT   ,Z,X,C,V,B,               B,N,M,COMM,DOT,SLSH,RSFT,0,\
			LCTRL,LGUI,LALT,MHEN,BSPC,SPC,  ENT,ESC,HENK,RALT,RGUI,RCTRL\
			),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
