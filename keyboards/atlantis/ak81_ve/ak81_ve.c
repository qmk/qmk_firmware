/* Copyright 2022 @fOmey
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

#if defined(ENCODER_ENABLE) && !defined(ENCODER_MAP_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        switch (get_highest_layer(layer_state)) {
          case 0:
            tap_code(KC_VOLU);
            break;
          case 1:
            rgb_matrix_step();
            break;
          default:
            tap_code(KC_VOLU);
            break;
        }
      }
    else {
        switch (get_highest_layer(layer_state)) {
          case 0:
            tap_code(KC_VOLD);
            break;
          case 1:
            rgb_matrix_step_reverse();
            break;
          default:
            tap_code(KC_VOLD);
            break;
        }
    }
    return true;
}
#endif
