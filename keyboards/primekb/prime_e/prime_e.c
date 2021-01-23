/* Copyright 2019 Holten Campbell
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
#include "prime_e.h"

void matrix_init_kb(void) {
    // set CapsLock LED to output and low
    setPinOutput(B1);
    writePinLow(B1);
    // set NumLock LED to output and low
    setPinOutput(B2);
    writePinLow(B2);
    // set ScrollLock LED to output and low
    setPinOutput(B3);
    writePinLow(B3);

    matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(B2);
    } else {
        writePinLow(B2);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(B1);
    } else {
        writePinLow(B1);
    }
    /*
      if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(B3);
      } else {
        writePinLow(B3);
      }*/

    led_set_user(usb_led);
}
