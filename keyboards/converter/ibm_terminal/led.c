/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include "ps2.h"
#include "led.h"

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        uint8_t ps2_led = 0;
        if (led_state.scroll_lock)
            ps2_led |= (1<<PS2_LED_SCROLL_LOCK);
        if (led_state.num_lock)
            ps2_led |= (1<<PS2_LED_NUM_LOCK);
        if (led_state.caps_lock)
            ps2_led |= (1<<PS2_LED_CAPS_LOCK);
        ps2_host_set_led(ps2_led);
    }
    return false;
}
