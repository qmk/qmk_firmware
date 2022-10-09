/*
Copyright 2021 rookiebwoy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "config_common.h"

/* Column/Row IO definitions */
#define MATRIX_ROWS 6
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { B4, E6, D7, B3, B2, B6 }
#define MATRIX_COL_PINS { B5, C6, D4 }

/* Bootmagic - hold down top left button while plugging in to enter bootloader */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* Tap interval for tap dance */
#define TAPPING_TERM 400

/* Oneshot interval */
#define ONESHOT_TIMEOUT 5000
