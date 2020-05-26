/* Copyright 2019 Spaceman
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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xB195
#define DEVICE_VER      0x0001
#define MANUFACTURER    Spaceman
#define PRODUCT         DDG_56
#define DESCRIPTION     DDG_56

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { B5, B15, B9, B10, A14 }
#define MATRIX_COL_PINS { A2, B8, B13, B14, B4, B11, B12, A13, A15, A8, A7, A6, B0, B1 }

#define QMK_SPEAKER A5

#define ENCODERS_PAD_A { A1, B3 }
#define ENCODERS_PAD_B { A0, B2 }
