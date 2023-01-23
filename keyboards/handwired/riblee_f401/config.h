/* Copyright 2020 Daniel Reibl <janos.daniel.reibl@protonmail.com>
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

#define MATRIX_ROWS 5
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { A6, A5, A4, A3, A2 }
#define MATRIX_COL_PINS { B10, B1, B0, B15, A8, B3, B4, B5, B6, B7, B8, B9 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN           A0
#define BACKLIGHT_LEVELS         5

#define MOUSEKEY_INTERVAL 32

#define TAPPING_TERM 175