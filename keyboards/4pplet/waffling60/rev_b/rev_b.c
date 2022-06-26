/*
Copyright 2020 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#include "rev_b.h"

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (CAPS_LOCK_ENABLE && res) {
        if(led_state.caps_lock) {
            #ifdef CAPS_LOCK_COLOR
                rgblight_sethsv_at(CAPS_LOCK_COLOR, 0);
            #else
                rgblight_sethsv_at(rgblight_get_hue(),rgblight_get_sat(),rgblight_get_val(), 0);
            #endif
        }
        else{
            rgblight_sethsv_at(HSV_OFF, 0);
        }
    }
    return res;
}
