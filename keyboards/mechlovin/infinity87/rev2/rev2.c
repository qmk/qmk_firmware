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
}

void led_init_ports(void) {
    setPinOutput(A3);
    writePinLow(A3);
    setPinOutput(A4);
    writePinLow(A4);
    setPinOutput(A8);
    writePinHigh(A8);
    setPinOutput(A0);
    writePinHigh(A0);
    setPinOutput(A1);
    writePinHigh(A1);
    setPinOutput(A2);
    writePinHigh(A2);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(A4, led_state.caps_lock);
        writePin(A3, led_state.num_lock);
        writePin(A8, led_state.scroll_lock);
    }

    return true;
}


uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 1, turn on D2 LED, otherwise off.
    if (biton32(state) == 0) {
        writePinLow(A0);
        writePinHigh(A1);
        writePinLow(A2);
    }
  // if on layer 2, turn on D1 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinLow(A0);
        writePinLow(A1);
        writePinLow(A2);
    }

  // if on layer 3, turn on D0 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinHigh(A0);
        writePinLow(A1);
        writePinLow(A2);
    }

  // if on layer 4, turn on D0 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinHigh(A0);
        writePinHigh(A1);
        writePinLow(A2);
    }

  // if on layer 5, turn on D0 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinLow(A0);
        writePinLow(A1);
        writePinHigh(A2);
    }

    return state;
}
