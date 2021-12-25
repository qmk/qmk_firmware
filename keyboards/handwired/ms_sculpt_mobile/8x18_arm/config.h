#/*
 * Copyright 2021 milestogo
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
#define VENDOR_ID     0xFEED
#define PRODUCT_ID    0x01ED
#define DEVICE_VER      0x0001

#define MANUFACTURER QMK
#define PRODUCT 8x18

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 18
#define DIODE_DIRECTION ROW2COL
#define MATRIX_HAS_GHOST

// V0
//#define MATRIX_ROW_PINS { B15, A8, A9, A10, A4, B14, A15, B3 }
//#define MATRIX_COL_PINS { B4, B5, B6, B7, B8, B9, B13, B11, B10, B1, B0, A7, A6, A3, A2, A1, A0, C15 }

// V1
#define MATRIX_COL_PINS { A7, B10, B1, B0, A6, A5, A4, A3, A2, A1, A0, B11, B8, B7, B6, B5, B4, B3 }
//#define MATRIX_ROW_PINS { A15, A10, A9, A8, B15, B14, B13, B12 } // flipped cable
#define MATRIX_ROW_PINS { B12, B13, B14, B15, A8, A9, A10, A15 }

// bitbanged RGB
#define RGB_DI_PIN B9

// the on-board LED for the bluepill board. 
// usually C13
#define STM32LED C13
