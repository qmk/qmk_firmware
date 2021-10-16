/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>

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

#include "zigotica.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state)){
        case _VIM:
            if (index == 0) { // LEFT
                // Cycle through buffers
                if (clockwise) {
                    register_code(KC_ESC);
                    SEND_STRING(":bprevious");
                    register_code(KC_ENT);
                    unregister_code(KC_ESC);
                    unregister_code(KC_ENT);
                } else {
                    register_code(KC_ESC);
                    SEND_STRING(":bnext");
                    register_code(KC_ENT);
                    unregister_code(KC_ESC);
                    unregister_code(KC_ENT);
                }
            } else { // RIGHT
                // Scroll
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
            }
        break;
        case _BROWSER:
            if (index == 0) { // LEFT
                // Cycle through Tabs
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                    /* register_code16(G(KC_RCBR)); */
                    /* unregister_code16(G(KC_RCBR)); */
                } else {
                    tap_code16(S(C(KC_TAB)));
                    /* register_code16(G(KC_LCBR)); */
                    /* unregister_code16(G(KC_LCBR)); */
                }
            } else { // RIGHT
                // Scroll up/down
                if (clockwise) {
                    register_code(KC_WH_U);
                    unregister_code(KC_WH_U);
                } else {
                    register_code(KC_WH_D);
                    unregister_code(KC_WH_D);
                }
            }
        break;
        case _FIGMA:
            if (index == 0) { // LEFT
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else { // RIGHT
                // Zoom in/out
                if (clockwise) {
                    register_code(KC_LGUI);
                    register_code(KC_WH_D);
                    unregister_code(KC_WH_D);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LGUI);
                    register_code(KC_WH_U);
                    unregister_code(KC_WH_U);
                    unregister_code(KC_LGUI);
                }
            }
        break;
        case _TERMINAL:
        default:
            if (index == 0) { // LEFT
                // Volume control.
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else { // RIGHT
                // Scroll
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
            }
        break;
    }
    return false;
}


