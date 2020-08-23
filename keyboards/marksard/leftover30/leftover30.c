/* Copyright 2020 marksard
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

#include "leftover30.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void keyboard_pre_init_user(void) {
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(D1);
  /* Set NUMLOCK indicator pin as output */
  setPinOutput(D2);
}

__attribute__((weak)) bool led_set_keymap(uint8_t usb_led) { return false; }

void led_set_user(uint8_t usb_led) {

  if (led_set_keymap(usb_led)) return;

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(D1);
  }
  else {
    writePinLow(D1);
  }

  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(D2);
  }
  else {
    writePinLow(D2);
  }
}
