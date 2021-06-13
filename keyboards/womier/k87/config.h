/* Copyright 2020 Adam Honse <calcprogrammer1@gmail.com>
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

/* USB Device descriptor parameter HID\VID_320F&PID_502A&REV_0101&MI_00
*/
#define VENDOR_ID              0xFEED
#define PRODUCT_ID             0x4B43
#define DEVICE_VER             0x0001

#define MANUFACTURER    Womier
#define PRODUCT         k87
#define DESCRIPTION     k87

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, B0, B1 }
#define MATRIX_ROW_PINS { C15, D11, D10, D9, D8, D7 }

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL//RGB_MATRIX_SOLID_COLOR

// #define RGB_MATRIX_STARTUP_HUE (157-8)

// #define RGB_MATRIX_STARTUP_SAT (192+16) //UINT8_MAX

// #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

#include "config_led.h"
