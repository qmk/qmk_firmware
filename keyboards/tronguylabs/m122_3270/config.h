/* Copyright 2021 James R. Maynard III <jaymaynard@gmail.com>
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

#define VENDOR_ID    0x1209
#define PRODUCT_ID   0x3270
#define MANUFACTURER IBM
#define PRODUCT      Model M PC/3270 122 key

// Both controllers draw 100 mA or less
#define USB_MAX_POWER_CONSUMPTION 100

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 20

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 15
