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

#define DEVICE_VER      0x0001

#define MATRIX_ROW_PINS \
    { D4, D7, B6, B4, B7 }
#define MATRIX_COL_PINS \
    { F1, B0, B1, B2, B3, D0, D1, D2, C6, C7, F7, F6, F5, F4, B5 }
#define UNUSED_PINS \
    { D4, D5, F0, B7 }
#define RGB_DI_PIN E6

