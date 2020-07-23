/* Copyright 2017 Zach White <skullydazed@gmail.com>
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
#include "2018.h"

void matrix_init_kb(void) {
	// Set our LED pins as output
	DDRB |= (1<<4);  // Numlock
	DDRB |= (1<<5);  // Capslock
	DDRB |= (1<<6);  // Scroll Lock

	// Run the keymap level init
	matrix_init_user();
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
  // Toggle numlock as needed
	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
		PORTB |= (1<<4);
	} else {
		PORTB &= ~(1<<4);
	}

  // Toggle capslock as needed
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		PORTB |= (1<<5);
	} else {
		PORTB &= ~(1<<5);
	}

	// Toggle scrolllock as needed
	if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
		PORTB |= (1<<6);
	} else {
		PORTB &= ~(1<<6);
	}
}
