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
#include "quantum.h"

void keyboard_pre_init_kb(void) {
	//Backlight LEDs Output Low
	gpio_set_pin_output(D6);
	gpio_write_pin_low(D6);
	
	//RGB power output low
	gpio_set_pin_output(E2);
	gpio_write_pin_low(E2);
	
	//Bluetooth power output high
	gpio_set_pin_output(B2);
	gpio_write_pin_low(B2);
	
	//RGB data output low
	gpio_set_pin_output(B3);
	gpio_write_pin_low(B3);
	
	keyboard_pre_init_user();
}
