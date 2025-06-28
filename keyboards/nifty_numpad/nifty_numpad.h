/* Copyright 2023 Acliad
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

enum custom_keycodes {
    RGB_DEF = QK_KB,
    RGB_IEF
};
#define LAYER_RGB (MAX_LAYER - 1)

#ifdef RGB_IDLE_ENABLE

#define RGB_IDLE_TIMEOUT_MS (10*60*1000)

// Functions exposed by nifty_numpad.c
bool rgb_matrix_idle_mode(void);

#endif
