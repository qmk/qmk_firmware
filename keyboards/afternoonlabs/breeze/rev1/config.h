/* Copyright 2021 Afternoon Labs
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

/* USB Device descriptor parameter */
#define VENDOR_ID 0x616C
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001
#define MANUFACTURER AfternoonLabs
#define PRODUCT Breeze

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

// wiring of each half
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, B1 }
#define MATRIX_COL_PINS \
    { B2, D1, D0, D4, C6, D7, E6, B4, B5 }

#define SPLIT_HAND_PIN B3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define SOFT_SERIAL_PIN D2

#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW_RIGHT 0
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5
#define BOOTMAGIC_LITE_ROW_LEFT 0
#define BOOTMAGIC_LITE_COLUMN_LEFT 5
