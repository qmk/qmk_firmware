/* Copyright 2020 bemeier
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

#include "config_common.h"

#define MATRIX_ROW_PINS \
    { F4, F5, D7, B5, B4 }
#define MATRIX_COL_PINS \
    { F6, B0, B1, F7, C7, C6, B6, F1, B2, B3, D6, D3, D2, D1, D0 } 
#define UNUSED_PINS \
    { D4, D5, F0, B7 }

#define RGB_DI_PIN E6
