/* Copyright 2019 iw0rm3r
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
#include "modelm101.h"

void keyboard_pre_init_kb(void) {
  /* Setting status LEDs pins to output and +5V (off) */
  setPinOutput(B4);
  setPinOutput(B5);
  setPinOutput(B6);
  writePinHigh(B4);
  writePinHigh(B5);
  writePinHigh(B6);
}

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    writePinLow(B4);
  } else {
    writePinHigh(B4);
  }
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    writePinLow(B6);
  } else {
    writePinHigh(B6);
  }
  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    writePinLow(B5);
  } else {
    writePinHigh(B5);
  }

  led_set_user(usb_led);
}
