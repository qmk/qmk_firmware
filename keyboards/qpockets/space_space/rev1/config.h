/* Copyright 2020 qpockets
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
#define VENDOR_ID 0x7170
#define PRODUCT_ID 0x7373
#define DEVICE_VER 0x3000
#define MANUFACTURER qpockets
#define PRODUCT space_space

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

#define MATRIX_ROW_PINS \
    { F1, F4, F5, C7 }
#define MATRIX_COL_PINS \
    { D4, B4, B5, B6, C6, F7, F6, F0, B0, E6, B1 }

#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* ROTARY ENCODERS */
#define ENCODERS_PAD_A \
    { B3, D6 }
#define ENCODERS_PAD_B \
    { B2, D7 }

#define ENCODER_RESOLUTIONS \
    { 3, 4 }
//#define ENCODER_DIRECTION_FLIP

#define DEBOUNCE 7

#define LOCKING_SUPPORT_ENABLE
