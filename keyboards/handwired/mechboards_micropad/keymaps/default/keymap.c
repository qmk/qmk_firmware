/* Copyright 2019 Yiancar
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

uint8_t led_state = 1;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MECHBOARDURL = SAFE_RANGE,
  QMKURL,
  MKUK,
  LEDCHANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    MECHBOARDURL,  QMKURL,  MKUK,  LEDCHANGE \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MECHBOARDURL:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("https://mechboards.co.uk/" SS_TAP(X_ENTER));
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
    case MKUK:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("MKUK4 was amazing!");
      } else {
        // when keycode QMKURL is released
      }
      break;
    case LEDCHANGE:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        led_state = !led_state;
        writePin(F6, led_state);
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
  setPinOutput(F6);
  writePinLow(F6);
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
