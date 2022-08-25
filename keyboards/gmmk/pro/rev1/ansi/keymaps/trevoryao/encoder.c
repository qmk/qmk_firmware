/* Copyright 2022 Trevor J. Yao @trevoryao

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

#include "encoder.h"

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

void encoder_action_cmd_scroll(bool clockwise) {
    if (clockwise) tap_code(KC_UP);
    else tap_code(KC_DOWN);
}

void encoder_action_rgb_brightness(bool clockwise) {
    if (clockwise) rgb_matrix_increase_val_noeeprom();
    else rgb_matrix_decrease_val_noeeprom();
}

void encoder_action_rgb_layer(bool clockwise) {
    if (clockwise) step_colour_layer();
    else reverse_colour_layer();
}

void encoder_action_rgb_speed(bool clockwise) {
    if (clockwise) rgb_matrix_increase_speed_noeeprom();
    else rgb_matrix_decrease_speed_noeeprom();
}
