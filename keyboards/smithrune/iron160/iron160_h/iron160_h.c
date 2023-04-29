/*
Copyright 2022 Gondolindrim

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

// Defining indicator colors
uint8_t caps_color[3] = {0x33,0x33,0x33};

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        led_state.caps_lock ? rgblight_setrgb_at(caps_color[0], caps_color[1], caps_color[2], 0) : rgblight_setrgb_at(0x00,0x00,0x00,0);
    }
    return res;
}
