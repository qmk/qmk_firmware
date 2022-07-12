/* Copyright 2022 TW59420 <https://github.com/TW59420>
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

#include "mw80.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {

}, {
    { 224, 32 }, { 179, 32 }, { 134, 32 }, { 90, 32 }, { 45, 32 }, { 0, 32 },
    { 224, 32 }, { 199, 32 }, { 174, 32 }, { 149, 32 }, { 125, 32 }, { 100, 32 }, { 75, 32 }, { 50, 32 }, { 25, 32 }, { 0, 32 }
}, {
    1, 1, 1, 1, 1, 1,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3
} };
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif
