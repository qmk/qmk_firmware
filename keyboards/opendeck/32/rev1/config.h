/* Copyright 2020 cmdremily
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

// USB Device descriptor parameter
#define VENDOR_ID 0x4345
#define PRODUCT_ID 0x2EC0
#define DEVICE_VER 0x0001
#define MANUFACTURER OpenDeck
#define PRODUCT OpenDeck32

// Key matrix (TtB, LtR)
#define MATRIX_ROWS 4
#define MATRIX_COLS 8
#define MATRIX_COL_PINS \
    { B4, D7, D6, D4, F7, F6, F5, F4 }
#define MATRIX_ROW_PINS \
    { C7, C6, B6, B5 }
#define DIODE_DIRECTION COL2ROW

// RGB matrix
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL (4 * 8 * 3)
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL)
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_SPIRAL
#define RGB_MATRIX_DISABLE_KEYCODES

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

#define FORCE_NKRO

// Slim down the ROM
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
