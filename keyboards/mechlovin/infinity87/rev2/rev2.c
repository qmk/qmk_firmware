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

#include "infinity87.h"

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

uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 0, turn on C6 LED, otherwise off.
    if (biton32(state) == 0) {
        writePinLow(C6);
    } else {
        writePinHigh(C6);
    }
  // if on layer 1, turn on C7 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinLow(C7);
    } else {
        writePinHigh(C7);
    }
  // if on layer 2, turn on A7 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinLow(A7);
    } else {
        writePinHigh(A7);
    }

  // if on layer 3, turn on A6 LED, otherwise off.
    if (biton32(state) == 3) {
        writePinLow(A6);
    } else {
        writePinHigh(A6);
    }

  // if on layer 4, turn on A5 LED, otherwise off.
    if (biton32(state) == 4) {
        writePinLow(A5);
    } else {
        writePinHigh(A5);
    }

    return state;
}
