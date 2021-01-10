/* Copyright 2020 Pylon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "boston.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(A0);
    setPinOutput(A1);
    setPinOutput(A2);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    /* this is to set an LED color at startup so it's not some random color*/
    rgblight_enable_noeeprom(); 
    rgblight_sethsv_noeeprom(0, 0, 128); 
    keyboard_post_init_user();
}


bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(A0, led_state.num_lock);
        writePin(A1, led_state.caps_lock);
        writePin(A2, led_state.scroll_lock);
    }

    return true;
}
