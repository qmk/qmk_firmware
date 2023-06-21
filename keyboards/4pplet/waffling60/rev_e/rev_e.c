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
#include "rev_e.h"

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

// This will be overridden by encoder map in all default keymaps, but serves as a catch-all for user keymaps that may omit the map.
#if defined (ENCODER_ENABLE) && !defined (ENCODER_MAP_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif
