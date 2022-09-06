/*
 * Copyright 2020 Richard Titmuss <richard.titmuss@gmail.com>
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
/* VID & PID from vusb project, see tmk_core/protocol/vusb/USB-IDs-for-free.txt"*/
#define VENDOR_ID 0x7274
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0000
#define MANUFACTURER richard.titmuss
#define PRODUCT Torn

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS \
    { D4, D1, D0, D5 }
#define MATRIX_COL_PINS \
    { B3, B4, B5, B0, D7, D6 }
#define UNUSED_PINS

#define SECONDARY_ROW_PINS \
    { (1 << 5), (1 << 6), (1 << 7), (1 << 4) }
#define SECONDARY_COL_PINS \
    { (1 << 3), (1 << 2), (1 << 1), (1 << 0), (1 << 15), (1 << 14) }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A \
    { B2 }
#define ENCODERS_PAD_B \
    { B1 }

#define USB_MAX_POWER_CONSUMPTION 100

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define OLED_TIMEOUT 60000
