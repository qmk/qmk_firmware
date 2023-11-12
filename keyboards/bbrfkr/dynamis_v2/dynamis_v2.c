/* Copyright 2023 bbrfkr
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

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (clockwise) {
        tap_code(layer_state == 0 ? KC_WH_D : KC_VOLD);
    } else {
        tap_code(layer_state == 0 ? KC_WH_U : KC_VOLU);
    }
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_F18:
            if (record->event.pressed) {
                const int cpi = pointing_device_get_cpi();
                const int next_cpi = cpi + 100;
                if (next_cpi <= 12000) {
                    pointing_device_set_cpi(next_cpi);
                }
                else {
                    pointing_device_set_cpi(12000);
                }
            }
            return false;
        case KC_F19:
            if (record->event.pressed) {
                const int cpi = pointing_device_get_cpi();
                const int next_cpi = cpi - 100;
                if (next_cpi >= 100) {
                    pointing_device_set_cpi(next_cpi);
                }
                else {
                    pointing_device_set_cpi(100);
                }
            }
            return false;
    }
    return true;
}
