/* Copyright 2020 Paul James
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
#define VENDOR_ID 0x706A
#define PRODUCT_ID 0x0002
#define DEVICE_VER 0x0001
#define MANUFACTURER Peej
#define PRODUCT Lumberjack

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 10
#define MATRIX_ROW_PINS { C0, B5, B4, B3, B2, B1 }
#define MATRIX_COL_PINS { B0, D7, D6, D5, D4, D1, D0, C1, C2, C3 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define USB_MAX_POWER_CONSUMPTION 100

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Encoder */
#define ENCODERS_PAD_A { C4 }
#define ENCODERS_PAD_B { C5 }
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10
