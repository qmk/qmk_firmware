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

void keyboard_post_init_kb(void) {
     setPinOutput(LED_CAPS);
     setPinOutput(LED_IND1);
     setPinOutput(LED_IND2);
     setPinOutput(LED_IND3);
     setPinOutput(LED_IND4);
     setPinOutput(LED_IND5);
     setPinOutput(LED_IND6);
     setPinOutput(LED_IND7);
     setPinOutput(LED_IND8);
     keyboard_post_init_user();
}

void led_update_ports(led_t led_state) {
    writePin(LED_CAPS, led_state.caps_lock);
    writePin(LED_IND1, led_state.caps_lock);
    writePin(LED_IND2, led_state.num_lock);
    writePin(LED_IND3, led_state.scroll_lock);
    writePin(LED_IND4, led_state.scroll_lock);
    writePin(LED_IND6, led_state.scroll_lock);
    writePin(LED_IND5, led_state.num_lock);
    writePin(LED_IND8, led_state.num_lock);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    if (get_highest_layer(state) > 0) writePin(LED_IND7, 1);
    else writePin(LED_IND7, 0);
    return layer_state_set_user(state);
}
