/* Copyright 2023 Paulo Pereira
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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


#pragma once
#include QMK_KEYBOARD_H

typedef struct {
  uint16_t keycode;
  uint16_t shifted_keycode;
} custom_shift_key_t;

extern const custom_shift_key_t custom_shift_keys[];
extern uint8_t NUM_CUSTOM_SHIFT_KEYS;

bool process_custom_shift_keys(uint16_t keycode, keyrecord_t *record);