/* Copyright 2024 RarePotato8DE
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

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(0, 0, 255, 0);
    } else {
        rgb_matrix_set_color(0, 0, 0, 0);
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(1, 0, 255, 0);
    } else {
        rgb_matrix_set_color(1, 0, 0, 0);
    }
    return false;
}
