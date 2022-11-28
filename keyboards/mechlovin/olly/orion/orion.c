/* Copyright 2022 Mechlovin' Studio
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

#include "orion.h"

void led_init_ports(void) {
  setPinOutput(B5);
  setPinOutput(B6);
  setPinOutput(B7);
  setPinOutput(B8);
  setPinOutput(B9);

}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            writePinHigh(B7);
            writePinLow(B6);
            writePinLow(B5);
            writePinLow(B8);
            writePinLow(B9);
            break;
        case 1:
            writePinHigh(B6);
            writePinLow(B7);
            writePinLow(B5);
            writePinLow(B8);
            writePinLow(B9);
            break;
        case 2:
            writePinHigh(B5);
            writePinLow(B7);
            writePinLow(B6);
            writePinLow(B8);
            writePinLow(B9);
            break;
        case 3:
            writePinHigh(B8);
            writePinLow(B7);
            writePinLow(B5);
            writePinLow(B6);
            writePinLow(B9);
            break;
        case 4:
            writePinHigh(B9);
            writePinLow(B7);
            writePinLow(B5);
            writePinLow(B8);
            writePinLow(B6);
            break;
    }
    return state;
}
