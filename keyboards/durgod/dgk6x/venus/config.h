/* Copyright 2021 Jessica Sullivan and Don Kjer
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
#define PRODUCT_ID      0x7EC5
#define DEVICE_VER      0x0001
#define PRODUCT         DURGOD Venus (QMK)

/* key matrix rows */
#define MATRIX_ROWS 5
#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4 }

/* key matrix columns */
#define MATRIX_COLS 14
#define MATRIX_COL_PINS { B0, B1, B2, B10, B11, B12, B13, B14, B15, C6, C7, C8, C9, C10 }

#ifdef RGB_MATRIX_ENABLE
#define DRIVER_1_LED_TOTAL 53
#define DRIVER_2_LED_TOTAL 8
#endif
