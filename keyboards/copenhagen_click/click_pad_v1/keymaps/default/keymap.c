/* Copyright 2019 mini-ninja-64
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
  COPENHAGEN = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( COPENHAGEN ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COPENHAGEN:
      if (record->event.pressed) {
        // when keycode COPENHAGEN is pressed
        SEND_STRING("Copenhagen Click!");
      } else {
        // when keycode COPENHAGEN is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
  backlight_enable();
  breathing_enable();

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
