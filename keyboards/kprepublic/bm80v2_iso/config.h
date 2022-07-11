/* Copyright 2022 bdtc123 *
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
#define VENDOR_ID       0x4B50
#define PRODUCT_ID      0x1142
#define DEVICE_VER      0x0002
#define MANUFACTURER    KP republic
#define PRODUCT         bm80v2_iso

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17
#define MATRIX_ROW_PINS { C7, C6, B6, F5, F7, F6 }
#define MATRIX_COL_PINS { E6, F0, F1, F4, D7, D6, B7, B1, B0, B2, B3, D3, D5, D4, D2, B4, B5 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#define DRIVER_ADDR_1 0b0110000
#define DRIVER_ADDR_2 0b0110000 // this is here for compliancy reasons.
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 88
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
