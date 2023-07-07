/*
Copyright 2023 Alberto Pavano "ATron789" <albertopavano@gmail.com>

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

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MS_WH_DOWN);
                } else {
                    tap_code(KC_MS_WH_UP);
                }
            }
            break;
        case _RAISE:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_WH_R);
                } else {
                    tap_code(KC_WH_L);
                }
            }
            break;
        case _LOWER:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_END);
                } else {
                    tap_code(KC_HOME);
                }
            }
            break;
        case _ADJUST:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_MS_RIGHT);
                } else {
                    tap_code(KC_MS_LEFT);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MS_DOWN);
                } else {
                    tap_code(KC_MS_UP);
                }
            }
            break;
    }
    return true;
}
#endif
