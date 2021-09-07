/* Copyright 2021 e3w2q
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

#define _DEFAULT 0
#define _LAYER1 1

enum encoder_number {
  _1ST_ENC = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT( /* Base */ 
    KC_P7,    KC_P8,    KC_P9,    KC_NLCK,
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,    KC_ENT, 
    KC_P0,    SEND_00,  LT(2,KC_PDOT),  KC_COMM,
    KC_LEFT,  KC_RGHT  // for encoders
  ),

  [1] = LAYOUT(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX
  ),

  [2] = LAYOUT(
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,
    RGB_RMOD, RGB_SPI,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  RGB_SPD,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX
  ),
};

keyevent_t encoder1_cw = {
  .key = (keypos_t){.row = 0, .col = 16},
  .pressed = false
};

keyevent_t encoder1_ccw = {
  .key = (keypos_t){.row = 0, .col = 17},
  .pressed = false
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
  if (IS_PRESSED(encoder1_cw)) {
    encoder1_cw.pressed = false;
    encoder1_cw.time = (timer_read() | 1);
    action_exec(encoder1_cw);
  }

  if (IS_PRESSED(encoder1_ccw)) {
    encoder1_ccw.pressed = false;
    encoder1_ccw.time = (timer_read() | 1);
    action_exec(encoder1_ccw);
  }
}

void led_set_user(uint8_t usb_led) {

}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == _1ST_ENC) { /* First encoder */
    if (clockwise) {
      encoder1_cw.pressed = true;
      encoder1_cw.time = (timer_read() | 1);
      action_exec(encoder1_cw);
    } else {
      encoder1_ccw.pressed = true;
      encoder1_ccw.time = (timer_read() | 1);
      action_exec(encoder1_ccw);
    }
  }

  return true;
}
