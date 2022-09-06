/* Copyright 2021 Matteo Bonora
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
#define PRODUCT_ID      0x0F34
#define DEVICE_VER      0x0001
#define MANUFACTURER    Hi-Tek
#define PRODUCT         AIM-65

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

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
#define MATRIX_ROW_PINS { D0, D4, D7, E6, B4, B5, B3, B1 }
#define MATRIX_COL_PINS { D1, C6, B6, B2, F7, F6, F5, F4 }

#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B0
#define LED_PIN_ON_STATE 0
