/*
Copyright 2023 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // flips the display 180 degrees if offhand
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    // Default OLED code
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0,7);
    oled_write_P(led_state.caps_lock ? PSTR(" Caps Lock "): PSTR(" ScottoCMD "), false);

    return false;
}

#endif