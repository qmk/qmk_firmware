/*
Copyright 2023 Gondolindrim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

void keyboard_post_init_kb(void) {
    setPinOutput(CAPS_INDICATOR_PIN);
    setPinOutput(INDICATOR_1_PIN);
    setPinOutput(INDICATOR_2_PIN);
    setPinOutput(INDICATOR_3_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(CAPS_INDICATOR_PIN, led_state.caps_lock   );
        writePin(INDICATOR_1_PIN   , led_state.num_lock    );
        writePin(INDICATOR_2_PIN   , led_state.scroll_lock );
        writePin(INDICATOR_3_PIN   , led_state.caps_lock   );
    }
    return res;
void keyboard_post_init_kb(void) {
    gpio_set_pin_output(CAPS_INDICATOR_PIN);
    gpio_set_pin_output(INDICATOR_1_PIN);
    gpio_set_pin_output(INDICATOR_2_PIN);
    gpio_set_pin_output(INDICATOR_3_PIN);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(CAPS_INDICATOR_PIN, led_state.caps_lock);
        gpio_write_pin(INDICATOR_1_PIN, led_state.num_lock);
        gpio_write_pin(INDICATOR_2_PIN, led_state.scroll_lock);
        gpio_write_pin(INDICATOR_3_PIN, led_state.caps_lock);
    }
    return res;
}
