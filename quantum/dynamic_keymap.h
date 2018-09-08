/* Copyright 2017 Jason Williams (Wilba)
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

#ifndef DYNAMIC_KEYMAP_H
#define DYNAMIC_KEYMAP_H

#include <stdint.h>
#include <stdbool.h>

void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column);
uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column);
void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode);
void dynamic_keymap_clear_all(void);

// This overrides the one in quantum/keymap_common.c
// uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

#endif //DYNAMIC_KEYMAP_H
