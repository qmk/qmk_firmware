 /* Copyright 2021 Stanrc85
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

#include "stanrc85.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FN1_60:
        break;
    case _FN2_60:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
        break;
    case _DEFAULT:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_MULTISPLASH);
        break;
    case _QWERTY:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
        break;
    default: //  for any other layers, or the default layer
        break;
    }
    return state;
}
