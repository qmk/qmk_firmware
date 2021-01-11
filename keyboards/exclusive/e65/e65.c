/* Copyright 2019 Brice Figureau
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

#include "e65.h"

void matrix_init_kb(void) {
    setPinOutput(B6);
    matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(B6);
    } else {
        writePinLow(B6);
    }

    led_set_user(usb_led);
}
