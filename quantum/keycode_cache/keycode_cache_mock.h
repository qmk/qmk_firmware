/* Copyright 2025 Garretonzo
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

#pragma once

#include <stdint.h>
#include "quantum/action.h"

// Mock function declarations
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);
void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode);
uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column);
action_t action_for_keycode(uint16_t keycode);
action_t action_for_key(uint8_t layer, keypos_t key);

// Utility functions
uint8_t biton(uint8_t bits);
uint8_t biton16(uint16_t bits);
uint8_t biton32(uint32_t bits);

// Keyboard functions
void clear_keyboard_but_mods(void);
void clear_keyboard_but_mods_and_keys(void);
