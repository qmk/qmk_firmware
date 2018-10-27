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
#include "2x1800.h"

void matrix_init_kb(void) {
	// Set our LED pins as output
	DDRB |= (1<<4);  // Numlock
	DDRB |= (1<<5);  // Capslock
	DDRB |= (1<<6);  // Scroll Lock

	// JTAG disable for PORT F. write JTD bit twice within four cycles.
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);

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
	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
		// Turn numlock on
		PORTB |= (1<<4);
	} else {
		// Turn numlock off
		PORTB &= ~(1<<4);
	}
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		// Turn capslock on
		PORTB |= (1<<5);
	} else {
		// Turn capslock off
		PORTB &= ~(1<<5);
	}
	if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
		// Turn scroll lock on
		PORTB |= (1<<6);
	} else {
		// Turn scroll lock off
		PORTB &= ~(1<<6);
	}
}
