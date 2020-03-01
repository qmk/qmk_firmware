/* Copyright 2019 Josh Hinnebusch
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
#include "hineyg80.h"

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        // Turn numlock on
		writePinHigh(C6);
    } else {
        // Turn numlock off
	    writePinLow(C6);
    }
	if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        // Turn capslock on
		writePinHigh(B6);
    } else {
        // Turn capslock off
		writePinLow(B6);
    }
	if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        // Turn scrolllock on
	    writePinHigh(B5);
    } else {
        // Turn scrolllock off
		writePinLow(B5);
    }
}
