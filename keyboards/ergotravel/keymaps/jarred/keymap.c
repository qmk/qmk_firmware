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
    [_QW] = LAYOUT_ergotravel_grid_wrapper(
      QWERTY_L1, KC_NO, KC_NO, QWERTY_R1,
      QWERTY_L2, KC_NO, KC_NO, QWERTY_R2,
      QWERTY_L3, KC_NO, KC_NO, QWERTY_R3,
      QWERTY_4_12),
    
    [_LW] = LAYOUT_ergotravel_grid_wrapper(
      LOWER_L1, KC_NO, KC_NO, LOWER_R1,
      LOWER_L2, KC_NO, KC_NO, LOWER_R2,
      LOWER_L3, KC_NO, KC_NO, LOWER_R3,
      LOWER_4_12),
      
    [_NV] = LAYOUT_ergotravel_grid_wrapper(
      NAV_L1, KC_NO, KC_NO, NAV_R1,
      NAV_L2, KC_NO, KC_NO, NAV_R2,
      NAV_L3, KC_NO, KC_NO, NAV_R3,
      NAV_4_12),
    
    [_NP] = LAYOUT_ergotravel_grid_wrapper(
      NUMPAD_L1, KC_NO, KC_NO, NUMPAD_R1,
      NUMPAD_L2, KC_NO, KC_NO, NUMPAD_R2,
      NUMPAD_L3, KC_NO, KC_NO, NUMPAD_R3,
      NUMPAD_4_12),
      
    [_MS] = LAYOUT_ergotravel_grid_wrapper(
      MOUSE_L1, KC_NO, KC_NO, MOUSE_R1,
      MOUSE_L2, KC_NO, KC_NO, MOUSE_R2,
      MOUSE_L3, KC_NO, KC_NO, MOUSE_R3,
      MOUSE_4_12)
};
