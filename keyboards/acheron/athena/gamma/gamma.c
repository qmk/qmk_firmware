/* Copyright 2023 Gondolindrim <gondolindrim@acheronproject.com>
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

void led_init_ports(void) {
    // Call the keyboard pre init code.

    // Set our LED pins as output
    setPinOutput(A10);
    setPinOutput(B12);
    setPinOutput(B8);
    setPinOutput(C0);
}

void led_update_ports(led_t led_state) {
    writePin(A10, led_state.caps_lock);
    writePin(B12, led_state.scroll_lock);
    writePin(B8,  led_state.num_lock);
    writePin(C0,  led_state.num_lock);
}
