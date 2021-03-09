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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_00 = SAFE_RANGE,
  SEND_000
};
/*
enum layer_number {
    _DEFAULT = 0,
    _LAYER1,
};
*/
#define _DEFAULT 0
#define _LAYER1 1

enum encoder_number {
    _1ST_ENC = 0,
    _2ND_ENC,
    _3RD_ENC,
    _4TH_ENC,
    _5TH_ENC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DEFAULT] = LAYOUT( /* Base */ 
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LSHIFT, KC_MUTE
  ),

  [_LAYER1] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, RESET
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
  if (IS_LAYER_ON(_LAYER1)) {
    switch (index) {
      case _1ST_ENC:
        if (clockwise) {
          SEND_STRING("1R" SS_TAP(X_ENTER));
        } else {
          SEND_STRING("1L" SS_TAP(X_ENTER));
        }
        break;
      case _2ND_ENC:
        if (clockwise) {
          SEND_STRING("2R" SS_TAP(X_ENTER));
        } else {
          SEND_STRING("2L" SS_TAP(X_ENTER));
        }
        break;
      case _3RD_ENC:
        if (clockwise) {
          SEND_STRING("3R" SS_TAP(X_ENTER));
        } else {
          SEND_STRING("3L" SS_TAP(X_ENTER));
        }
        break;
      case _4TH_ENC:
        if (clockwise) {
          SEND_STRING("4R" SS_TAP(X_ENTER));
        } else {
          SEND_STRING("4L" SS_TAP(X_ENTER));
        }
        break;
      case _5TH_ENC:
        if (clockwise) {
          SEND_STRING("5R" SS_TAP(X_ENTER));
        } else {
          SEND_STRING("5L" SS_TAP(X_ENTER));
        }
        break;
    }
  } else {
    switch (index) {
      case _1ST_ENC:
        if (clockwise) {
          tap_code(KC_RIGHT);
        } else {
          tap_code(KC_LEFT);
        }
        break;
      case _2ND_ENC:
        if (clockwise) {
          tap_code(KC_DOWN);
        } else {
          tap_code(KC_UP);
        }
        break;
      case _3RD_ENC:
        if (clockwise) {
          tap_code(KC_PGDOWN);
        } else {
          tap_code(KC_PGUP);
        }
        break;
      case _4TH_ENC:
        if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
        } else {
          tap_code(KC_MS_WH_UP);
        }
        break;
      case _5TH_ENC:
        if (clockwise) {
          tap_code(KC_VOLU);
        } else {
          tap_code(KC_VOLD);
        }
        break;
    }
  }
}

