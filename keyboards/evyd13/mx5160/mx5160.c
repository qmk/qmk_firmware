/* Copyright 2019 Evy Dekkers
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
#include "mx5160.h"


void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

  matrix_init_user();
  led_init_ports();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)

  matrix_scan_user();
}

void led_init_ports(void) {
	//Set led pin as output, then high (off)
	
	//Caps lock
    setPinOutput(B1);
    writePinHigh(B1);
	
	//Num lock
    setPinOutput(B2);
    writePinHigh(B2);
	
	//Scroll lock
    setPinOutput(B3);
    writePinHigh(B3);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(B2, !led_state.num_lock);
        writePin(B1, !led_state.caps_lock);
        writePin(B3, !led_state.scroll_lock);
    }
    return res;
}
