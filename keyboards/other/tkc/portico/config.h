/*
Copyright 2020 Terry Mathews

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x544B //TK
#define PRODUCT_ID      0x0008
#define DEVICE_VER      0x0001
#define MANUFACTURER    TKC
#define PRODUCT         Portico

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B6, C6, C7, F7, D2 }
#define MATRIX_COL_PINS { D3, D5, D4, D6, D7, B4, B5, F6, F5, F4, F1, B0, B1, B2, B3 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26
#    define DEBOUNCE 3
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define DISABLE_RGB_MATRIX_SPLASH
#    define DISABLE_RGB_MATRIX_MULTISPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
#    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define DRIVER_ADDR_1 0x74
#    define DRIVER_ADDR_2 0x77
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 36
#    define DRIVER_2_LED_TOTAL 31
#    define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#endif
