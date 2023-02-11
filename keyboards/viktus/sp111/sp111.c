/* Copyright 2020 blindassassin111
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
#include "sp111.h"

void keyboard_pre_init_kb(void) {
    // enable built in pullups to avoid timeouts when right hand not connected
    setPinInputHigh(D0);
    setPinInputHigh(D1);

    keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    setPinOutput(F0);
    setPinOutput(F1);
    setPinOutput(F4);

    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(F0, led_state.num_lock);
        writePin(F1, led_state.caps_lock);
        writePin(F4, led_state.scroll_lock);
    }
    return res;
}
