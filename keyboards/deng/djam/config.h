/* Copyright 2022 Leo Deng (@myst729)
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

#define MATRIX_ROWS 3
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS { F0, F1, F4 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, D6, D4 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define BACKLIGHT_PIN B7
#define BACKLIGHT_LEVELS 5
