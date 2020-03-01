/* Copyright 2019 HnahKB
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
#include "stella.h"


void matrix_init_kb(void) {
  led_init_ports();
};

void led_init_ports(void) {
  setPinOutput(B3);     
  setPinOutput(B7);
}

void led_set_kb(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    // Turn Caps Lock LED on
    writePinLow(B3);
  } else {
    // Turn Caps Lock LED off
    writePinHigh(B3);
  }
  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    // Turn Scroll Lock LED on
    writePinLow(B7);
  } else {
    // Turn Scroll Lock LED off
    writePinHigh(B7);
  }
}
