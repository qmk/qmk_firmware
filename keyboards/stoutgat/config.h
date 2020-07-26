/*Copyright 2020 Thys de Wet

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

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x7811
#define DEVICE_VER 0x0001
#define MANUFACTURER TKW
#define PRODUCT stoutgat
#define DESCRIPTION A 65% ISO/ANSI with dual encoders

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define ENCODER_RESOLUTION 4

#define MATRIX_ROW_PINS { D1, D0, A0, A1, A2 }
#define MATRIX_COL_PINS { D6, D5, D7, C0, C1, C2, C3, C4, C5, C6, C7, A7, A6, A5, A4 }
#define ENCODERS_PAD_A { B4, B0 }
#define ENCODERS_PAD_B { B3, B1 }

#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define NO_UART 1
#define USB_MAX_POWER_CONSUMPTION 500
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif


/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
