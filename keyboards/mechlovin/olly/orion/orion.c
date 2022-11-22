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

layer_state_t layer_state_set_user(layer_state_t state)
{
  // if on layer 0, turn on B7 LED, otherwise off.
    if (biton32(state) == 0) {
        writePinHigh(B7);
    } else {
        writePinLow(B7);
    }
  // if on layer 1, turn on B6 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinHigh(B6);
    } else {
        writePinLow(B6);
    }
  // if on layer 2, turn on B5 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinHigh(B5);
    } else {
        writePinLow(B5);
    }
  // if on layer 3, turn on B8 LED, otherwise off.
    if (biton32(state) == 3) {
        writePinHigh(B8);
    } else {
        writePinLow(B8);
    }
  // if on layer 4, turn on B9 LED, otherwise off.
    if (biton32(state) == 4) {
        writePinHigh(B9);
    } else {
        writePinLow(B9);
    }

    return state;
}
