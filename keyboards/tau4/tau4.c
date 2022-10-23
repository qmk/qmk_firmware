/*
Copyright 2020 Oliver Gaskell <me@gaskell.tech>

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

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
        oled_write_P(PSTR("Tau.4 v1.0\n\n"), false);
        oled_write_P(PSTR("Layer:\n"), false);

        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Default  "), false);
                break;
            case 1:
                oled_write_P(PSTR("Numpad   "), false);
                break;
            case 2:
                oled_write_P(PSTR("Lower    "), false);
                break;
            case 3:
                oled_write_P(PSTR("Raise    "), false);
                break;
            case 4:
                oled_write_P(PSTR("Adjust   "), false);
                break;
            default:
                oled_write_P(PSTR("Undefined"), false);
        }
    return true;
}
#endif
