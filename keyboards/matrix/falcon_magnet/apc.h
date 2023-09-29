/**
 * Copyright 2023 astro
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

#ifndef APC_KEY_MIN
#define APC_KEY_MIN             2048
#endif

#ifndef APC_KEY_MAX
#define APC_KEY_MAX             4096
#endif

#ifndef APC_INTERVAL_MIN
#define APC_INTERVAL_MIN        50
#endif

#ifndef APC_INTERVAL_MAX
#define APC_INTERVAL_MAX        2048
#endif

#ifndef APC_INTERVAL_COUNT
#define APC_INTERVAL_COUNT      24
#endif

#ifndef APC_INTERVAL_INVALID
#define APC_INTERVAL_INVALID    0
#endif

#ifndef APC_INTERVAL_DEFAULT
#define APC_INTERVAL_DEFAULT    500
#endif

#ifndef APC_INTERVAL_INDEX
#define APC_INTERVAL_INDEX      5
#endif

#ifndef APC_THRESHOLD
#define APC_THRESHOLD           100
#endif

#ifndef APC_KEYMAP_DOWN_LAYER
#define APC_KEYMAP_DOWN_LAYER   4
#endif

#ifndef APC_KEYMAP_UP_LAYER
#define APC_KEYMAP_UP_LAYER     5
#endif

void apc_matrix_init(void);
bool apc_matrix_update(uint32_t row, uint32_t col, uint32_t value);
