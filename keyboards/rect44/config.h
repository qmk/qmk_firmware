/* Copyright 2020-2021 koshinoya
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
#define PRODUCT_ID      0x4DD7
#define DEVICE_VER      0x0001
#define MANUFACTURER    koshinoya
#define PRODUCT         Rect44

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* Key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, F5, F4 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, D1, D0, D4, C6, D7, E6, B4, B5 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN B6
#define RGBLED_NUM 12
#define RGBLIGHT_ANIMATIONS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
