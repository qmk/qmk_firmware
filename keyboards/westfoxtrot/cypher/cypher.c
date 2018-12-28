/* Copyright 2018 westfoxtrot
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
#include "cypher.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware

	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        PORTF |= (1<<4);
    } else {
        PORTF &= ~(1<<4);
    }
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        PORTF |= (1<<1);
    } else {
        PORTF &= ~(1<<1);
    }
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        PORTB |= (1<<5);
    } else {
        PORTB &= ~(1<<5);
    }
}
