/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "bbaserdem.h"

/* UNDERGLOW IMPLEMENTATION
 */

// Used to initialize layer switching overlay
void keyboard_post_init_underglow(void);
// Used to change RGB underglow layers on keymap layer change
layer_state_t layer_state_set_underglow(layer_state_t state);
// Hook into shutdown to show effect on shutdown
void shutdown_underglow(void);
