/* Copyright 2021 DongXing
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
#include "hotswap.h"

void matrix_init_kb(void) {
  setPinOutput(E6);
  
  matrix_init_user();
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(E6);
  } else {
    writePinHigh(E6);
  }
  led_set_user(usb_led);
}
