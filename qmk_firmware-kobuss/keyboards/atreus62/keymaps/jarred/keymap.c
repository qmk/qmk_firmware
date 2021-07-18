/* Copyright 2018 Jarred Steenvoorden
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
 
#include QMK_KEYBOARD_H
#include "jarred.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_atreus62_grid_wrapper(BLANK_12, QWERTY_1_12, QWERTY_2_12, QWERTY_3_12, QWERTY_L4, KC_NO, KC_NO, QWERTY_R4),
    [_LW] = LAYOUT_atreus62_grid_wrapper(BLANK_12, LOWER_1_12 , LOWER_2_12 , LOWER_3_12 , LOWER_L4 , KC_NO, KC_NO, LOWER_R4 ),
    [_NV] = LAYOUT_atreus62_grid_wrapper(BLANK_12, NAV_1_12   , NAV_2_12   , NAV_3_12   , NAV_L4   , KC_NO, KC_NO, NAV_R4   ),
    [_NP] = LAYOUT_atreus62_grid_wrapper(BLANK_12, NUMPAD_1_12, NUMPAD_2_12, NUMPAD_3_12, NUMPAD_L4, KC_NO, KC_NO, NUMPAD_R4),
    [_MS] = LAYOUT_atreus62_grid_wrapper(BLANK_12, MOUSE_1_12 , MOUSE_2_12 , MOUSE_3_12 , MOUSE_L4 , KC_NO, KC_NO, MOUSE_R4 )
};
