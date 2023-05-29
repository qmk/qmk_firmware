/* Copyright 2020 Nguyen Minh Hoang
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
    setPinOutput(B1);
    setPinOutput(B2);
    /* I will add function to these later */
    // setPinOutput(B3);
    // setPinOutput(E2);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B1, led_state.num_lock);
        writePin(B2, led_state.caps_lock);
    }
    return res;
}
