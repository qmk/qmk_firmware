/* Copyright 2021 Shulin Huang <mumu@x-bows.com>
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

#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x1228
#define DEVICE_VER   0x0001
#define MANUFACTURER X-BOWS
#define PRODUCT      NUMPAD

#define MATRIX_ROWS 6
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { B5, B4, C6, B6, D7, B3 }
#define MATRIX_COL_PINS { D4, D6, B2, B1 }
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 3

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_PROCESS_LIMIT 18
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#    define RGB_DISABLE_AFTER_TIMEOUT 0          // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED       // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define RGB_MATRIX_CENTER \
        { 30, 32 }

#    define DRIVER_ADDR_1 0b1110111
#    define DRIVER_COUNT 1
#    define DRIVER_1_LED_TOTAL 22
#    define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL)
#endif
