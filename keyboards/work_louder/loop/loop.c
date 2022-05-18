/* Copyright 2021 Work Louder
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

#include "loop.h"

#if !defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MPRV);
        } else {
            tap_code(KC_MNXT);
        }
    } else {
        if (clockwise) {
            rgb_matrix_step_reverse();
        } else {
            rgb_matrix_step();
        }
    }
    return true;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = {
    {
        {   NO_LED, NO_LED, NO_LED, 8, 7, 6, 5, 4, 3, 2, 1, 0 }
    }, {
        {188, 32}, {169, 32}, {150, 32}, {131, 32}, {112, 32}, {93, 32}, {74, 32}, {55, 32}, {36, 32}
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};
// clang-format on
#endif
