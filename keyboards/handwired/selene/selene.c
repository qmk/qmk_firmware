/* Copyright 2020 Bpendragon
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


#include "selene.h"

void matrix_init_kb(void){
    setPinOutput(A2);
    setPinOutput(A1);
    setPinOutput(A0);
}

void keyboard_post_init_user(void) {
    rgblight_setrgb(0xff, 0xff, 0xff);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(A0, led_state.num_lock);
        writePin(A2, led_state.caps_lock);
        writePin(A1, led_state.scroll_lock);
    }
    return res;
}
