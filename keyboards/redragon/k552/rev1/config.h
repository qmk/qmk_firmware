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
#include "config_led.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0C45
#define PRODUCT_ID      0x5104
#define DEVICE_VER      0x0001

#define MANUFACTURER    Redragon
#define PRODUCT         K552
#define DESCRIPTION     K552 Kumara

/* Additional options */
#define RGB_MATRIX_ENABLE 1
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_LED_PROCESS_LIMIT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 0
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_SPD 32

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define DIODE_DIRECTION ROW2COL

#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, A14, A15, B0, B1, B2, B3, B4, B10, B11 }
#define MATRIX_ROW_PINS { D15, D14, D13, D12, D11, D10 }

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE