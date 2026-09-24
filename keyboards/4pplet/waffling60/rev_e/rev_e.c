/*
Copyright 2022 Stefan Sundin "4pplet" <mail@4pplet.com>

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

#ifndef CAPS_LOCK_ENABLE
#    define CAPS_LOCK_ENABLE true
#endif

#ifndef CAPS_LOCK_COLOR
#    define CAPS_LOCK_COLOR HSV_GREEN
#endif

void keyboard_pre_init_kb(void) {
    rgblight_set_effect_range(0, 16);
    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (CAPS_LOCK_ENABLE && res) {
        if(led_state.caps_lock) {
            rgblight_sethsv_at(CAPS_LOCK_COLOR, 16);
        }
        else{
            rgblight_sethsv_at(HSV_OFF, 16);
        }
    }
    return res;
}
