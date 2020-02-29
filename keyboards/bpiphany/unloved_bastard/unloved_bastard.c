/* Copyright 2018 Alexander Fougner <fougner89 at gmail.com>
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
#include "unloved_bastard.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	led_init_ports();
	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

// C5 left
// C6 middle led
// B7 right led
void led_init_ports(void) {
    DDRB |= (1<<7);
    DDRC |= (1<<5);
    DDRC |= (1<<6);

    PORTB |= (1<<7);
    PORTC |= (1<<5);
    PORTC |= (1<<6);
}


void led_set_kb(uint8_t usb_led) {

    if (usb_led & (1<<USB_LED_CAPS_LOCK))
        PORTC &= ~(1<<5);
    else
        PORTC |=  (1<<5);

    if (usb_led & (1<<USB_LED_NUM_LOCK))
        PORTB &= ~(1<<7);
    else
        PORTB |=  (1<<7);

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
        PORTC &= ~(1<<6);
    else
        PORTC |=  (1<<6);

    led_set_user(usb_led);
}
