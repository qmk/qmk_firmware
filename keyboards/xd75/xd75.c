/* Copyright 2017 Benjamin Kesselring
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
#include "xd75.h"

#define XD75_CAPSLOCK_LED 2  // B2
#define XD75_GP103_LED 4  // F4
#define XD75_KEYCAPS_LED 5  // F5
#define XD75_GP100_LED 7  // F7

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	capslock_led_init();
	gp100_led_init();
	gp103_led_init();
	keycaps_led_init();

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
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

	led_set_user(usb_led);
}

void capslock_led_init(void) {
	DDRB |= (1 << XD75_CAPSLOCK_LED);
	capslock_led_off();
}

void capslock_led_off(void) {
	PORTB |= (1 << XD75_CAPSLOCK_LED);
}

void capslock_led_on(void) {
	PORTB &= ~(1 << XD75_CAPSLOCK_LED);
}

void gp100_led_init(void) {
	DDRF |= (1 << XD75_GP100_LED);
	gp100_led_off();
}

void gp100_led_off(void) {
	PORTF |= (1 << XD75_GP100_LED);
}

void gp100_led_on(void) {
	PORTF &= ~(1 << XD75_GP100_LED);
}

void gp103_led_init(void) {
	DDRF |= (1 << XD75_GP103_LED);
	gp103_led_off();
}

void gp103_led_off(void) {
	PORTF &= ~(1 << XD75_GP103_LED);
}

void gp103_led_on(void) {
	PORTF |= (1 << XD75_GP103_LED);
}

void keycaps_led_init(void) {
	DDRF |= (1 << XD75_KEYCAPS_LED);
	keycaps_led_off();
}

void keycaps_led_off(void) {
	PORTF |= (1 << XD75_KEYCAPS_LED);
}

void keycaps_led_on(void) {
	PORTF &= ~(1 << XD75_KEYCAPS_LED);
}
