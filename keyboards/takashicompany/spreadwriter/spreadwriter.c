/* Copyright 2021 takashicompany
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

#include "spreadwriter.h"

bool encoder_update_kb(uint8_t index, bool clockwise) {
    keypos_t key;
    if (index == 0) {
        if (clockwise) {
            key.row = 4;
            key.col = 0;
        } else {
            key.row = 0;
            key.col = 6;
        }
        uint8_t layer = layer_switch_get_layer(key);
        uint16_t keycode = keymap_key_to_keycode(layer, key);

        tap_code16(keycode);
        return false;
    }

    return true;
}
