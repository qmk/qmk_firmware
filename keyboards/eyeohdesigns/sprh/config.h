/*
Copyright 2021 Eye Oh Designs

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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER Eye Oh Designs
#define PRODUCT sprh

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
#define ENCODERS_PAD_A {D0}
#define ENCODERS_PAD_B {D1}
#define ENCODER_RESOLUTION 2


#define MATRIX_ROW_PINS { B3, B7, D2, D5, D3 }
#define MATRIX_COL_PINS { E6, F0, F1, F4, F5, F6, C6, B6, B5, B4, D7, D6, F7, D4 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5