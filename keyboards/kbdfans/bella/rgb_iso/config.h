/* Copyright 2021 dztech
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
#define VENDOR_ID       0x4B42
#define PRODUCT_ID      0x0009
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDFANS
#define PRODUCT         BELLA RGB ISO
/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B7, B6 }
#define MATRIX_COL_PINS { C6, C7, F7, F6, F5, F4, F1, F0, D2, D3, D5, D4, D6, D7, B4, B5 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 3

/* disable these deprecated features by default */
#ifdef RGB_MATRIX_ENABLE
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_LED_PROCESS_LIMIT 4
#define RGB_MATRIX_LED_FLUSH_LIMIT 26
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#define DRIVER_ADDR_1 0b0110000
#define DRIVER_ADDR_2 0b0110000 // this is here for compliancy reasons.
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 109
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#define DRIVER_INDICATOR_LED_TOTAL 0
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 2
