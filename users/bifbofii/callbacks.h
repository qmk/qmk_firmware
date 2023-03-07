/* Copyright 2023 Christoph Jabs (BifbofII)
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

#include "quantum.h"

// Weakly defined keymap variants of callbacks implemented
void          keyboard_post_init_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
bool          led_update_keymap(led_t led_state);
bool          oled_task_keymap(void);
void          housekeeping_task_keymap(void);
void          raw_hid_receive_keymap(uint8_t *data, uint8_t length);
