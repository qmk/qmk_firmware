/* Copyright 2019 e3w2q
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
 * along with this program.  If not, see <http://gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_00 = SAFE_RANGE,
  SEND_000
};

enum encoder_number {
    _1ST_ENC = 0,
    _2ND_ENC,
    _3RD_ENC,
    _4TH_ENC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-------------------------------
   *  | NmLk  KP/  KP*  Tab MO(1)XXXX 
   *  |  KP7  KP8  KP9  KP- Home XXXX 
   *  |  KP4  KP5  KP6  KP+  End XXXX 
   *  |  KP1  KP2  KP3 Entr PgUp XXXX 
   *  |  KP0   00    .   Up PgDn XXXX 
   *  |   BS  Del Left Down Rght XXXX 
   *  `-------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-------------------------------
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   */

  [0] = LAYOUT( /* Base */ 
    KC_H,     KC_M,     KC_J,     KC_O,     KC_E,     XXXXXXX,  
    C(KC_S),  C(KC_C),  KC_B,     KC_P,     C(KC_Z),  XXXXXXX,  
    KC_G,     C(KC_V),  KC_K,     KC_L,     C(KC_Y),  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_END,   XXXXXXX,  

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),

  [1] = LAYOUT(
    RGB_TOG,  RGB_MOD,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  
    RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  EEP_RST,  XXXXXXX,  
    RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  RESET,    XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_00:
      if (record->event.pressed) {
        // when keycode SEND_00 is pressed
        SEND_STRING("00");
      } else {
        // when keycode SEND_00 is released
      }
      break;
    case SEND_000:
      if (record->event.pressed) {
        // when keycode SEND_000 is pressed
        //SEND_STRING("000" SS_TAP(X_ENTER));
        SEND_STRING("000");
      } else {
        // when keycode SEND_000 is released
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

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
      case _1ST_ENC:
        if (clockwise) {
          tap_code(KC_PGDOWN);
        } else {
          tap_code(KC_PGUP);
        }
        break;
      case _2ND_ENC:
        if (clockwise) {
          tap_code(KC_INS);
        } else {
          tap_code(KC_DEL);
        }
        break;
      case _3RD_ENC:
        if (clockwise) {
          SEND_STRING("3RD_ENC_R");
        } else {
          SEND_STRING("3RD_ENC_L");
        }
        break;
      case _4TH_ENC:
        if (clockwise) {
          SEND_STRING("4TH_ENC_R");
        } else {
          SEND_STRING("4TH_ENC_L");
        }
        break;
    }
}

