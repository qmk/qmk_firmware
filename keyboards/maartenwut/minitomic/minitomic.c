/* Copyright 2019 Maarten Dekkers <maartenwut@gmail.com>
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
#include "minitomic.h"

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

    led_init_ports();
}

void led_init_ports(void) {
	//Set led pin as output, then high (off)
    writePinHigh(C7);
}

bool led_update_kb(led_t led_state) {
    // writePin sets the pin high for 1 and low for 0.
    // In this example the pins are inverted, setting
    // it low/0 turns it on, and high/1 turns the LED off.
    // This behavior depends on whether the LED is between the pin
    // and VCC or the pin and GND.
    writePin(C7, !led_state.caps_lock);
    return true;
}

