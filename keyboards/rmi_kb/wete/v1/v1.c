/* Copyright 2020 Ramon Imbao
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

#include "v1.h"

void keyboard_pre_init_user(void) {
    // Initialize indicator LED pins
    setPinOutput(A14); // Num Lock
    setPinOutput(A15); // Scroll Lock
    setPinOutput(B3); // Caps Lock
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(A14, !led_state.num_lock);
        writePin(A15, !led_state.scroll_lock);
        writePin(B3, !led_state.caps_lock);
    }

    return res;
}
