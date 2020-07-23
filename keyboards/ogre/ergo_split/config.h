/*
Copyright 2020 ctrlshiftba

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER ctrlshiftba
#define PRODUCT ergo_split
#define DESCRIPTION a keycap friendly ergo. the split version

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D3
#define SPLIT_HAND_PIN D1

#define RGB_DI_PIN B6
#define RGBLED_SPLIT { 7, 7 }
#define RGBLED_NUM 14
#define RGBLIGHT_LED_MAP { 6, 5, 4, 3, 2, 1, 0, 13, 12,11, 10, 9, 8, 7}
#define RGBLIGHT_ANIMATIONS
#define DEBOUNCE 5
