/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "alps64.h"

void keyboard_pre_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
    setPinOutput(C5);
    keyboard_pre_init_user();
}

void led_set_kb(uint8_t usb_led)
{
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        // output high
        writePinHigh(C5);
    } else {
        // Hi-Z
        writePinLow(C5);
    }

    led_set_user(usb_led);
}
