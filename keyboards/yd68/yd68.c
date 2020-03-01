/* Copyright 2018 Ryan "Izzy" Bales
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
#include "yd68.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	
	//Capslock LED Output Low
	DDRD |= (1<<4);
    PORTD &= ~(1<<4);
	
	//Backlight LEDs Output Low
	DDRD |= (1<<6);
    PORTD &= ~(1<<6);
	
	//RGB power output low
	DDRE |= (1<<2);
    PORTE &= ~(1<<2);
	
	//Bluetooth power output high
	DDRB |= (1<<2);
    PORTB |= (1<<2);
	
	//RGB data output low
	DDRB |= (1<<3);
	PORTB &= ~(1<<3);
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
	
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRD |= (1<<4);
        PORTD &= ~(1<<4);
    } else {
        // output high
        DDRD |= (1<<4);
        PORTD |= (1<<4);
    }
}
