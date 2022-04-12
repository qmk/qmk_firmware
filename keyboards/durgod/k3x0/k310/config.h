/* Copyright 2021 Don Kjer and Tyler Tidman
 * Copyright 2021 Simon Arlott
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
#define PRODUCT_ID      0x3100
// Taurus K310 models:
//#define DEVICE_VER      0x0001 // Base (no backlight)
//#define DEVICE_VER      0x0002 // Corona (white led matrix)
//#define DEVICE_VER      0x0003 // Aurora (red & blue led matrix)
//#define DEVICE_VER      0x0004 // Nebula (rgb led matrix)

/* key matrix size (cols in generic keyboard config) */
#define MATRIX_ROWS 8

#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, A5, A6, A7 }

/* LED indicator pins */
#define LED_NUM_LOCK_PIN    C8
