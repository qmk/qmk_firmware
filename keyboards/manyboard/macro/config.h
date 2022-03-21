/*
Copyright 2020 William Ehman

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
#define VENDOR_ID    0x4D42 // MB
#define PRODUCT_ID   0x0015 // 15 keys
#define DEVICE_VER   0x0103
#define MANUFACTURER Manyboard
#define PRODUCT      MB_Macro

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D1, D2, D3 }
#define MATRIX_COL_PINS { D4, D5, D6, D7 }
#define UNUSED_PINS

/*Encoder Pins*/
#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { C7 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* RGB Pins */
#define RGB_DI_PIN B6
#define RGBLED_NUM 2
#define RGBLIGHT_LIMIT_VAL 10

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
