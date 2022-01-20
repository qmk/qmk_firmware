/* Copyright 2020 Spaceman
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5342 // SB
#define PRODUCT_ID      0x5032 // P2
#define DEVICE_VER      0x0002
#define MANUFACTURER    Spaceman
#define PRODUCT         Pancake 2

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { C7, C6, B6, B5 }
#define MATRIX_COL_PINS { B7, B3, B2, B1 ,B0, E6, F0, F1, F4, F5, F6, F7 }
#define UNUSED_PINS
