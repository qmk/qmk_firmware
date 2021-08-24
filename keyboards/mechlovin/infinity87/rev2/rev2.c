/* Copyright 2020 Team Mechlovin'
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

#include "rev2.h"

void matrix_init_kb(void) {
  matrix_init_user();
  led_init_ports();
};
void led_init_ports(void) {
  setPinOutput(A5);
  setPinOutput(A6);
  setPinOutput(A7);
  setPinOutput(C7);
  setPinOutput(C6);

}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    writePinHigh(C6);
    writePinHigh(C7);
    writePinHigh(A7);
    writePinHigh(A6);
    writePinHigh(A5);
    switch (get_highest_layer(state)) {
        case 0:
	        writePinLow(C6);
	        break;
	    case 1:
	        writePinLow(C7);
	        break;
	    case 2:
	        writePinLow(A7);
	        break;
	    case 3:
	        writePinLow(A6);
	        break;
	     case 4:
	         writePinLow(A5);
	         break;
	}
    return state;
}
