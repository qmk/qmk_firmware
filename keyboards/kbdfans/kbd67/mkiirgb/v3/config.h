/* Copyright 2021 DZTECH <moyi4681@live.cn>
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
#define VENDOR_ID       0x4B42 // KB
#define PRODUCT_ID      0x1226
#define DEVICE_VER      0x0002
#define MANUFACTURER    KBDfans
#define PRODUCT         kbd67mkiirgb v3

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { F0, F1, F4, E6, C6 }
#define MATRIX_COL_PINS { F7, F6, F5, C7, B0, B1, B2, B3, B4, D7, D6, D4, D5, D3, D2}
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#ifdef RGB_MATRIX_ENABLE
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#define USB_SUSPEND_WAKEUP_DELAY 5000
#define RGB_MATRIX_KEYPRESSES
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN	
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define RGB_MATRIX_LED_PROCESS_LIMIT 4
#define RGB_MATRIX_LED_FLUSH_LIMIT 26
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#define DRIVER_ADDR_1 0b0110000
#define DRIVER_ADDR_2 0b0110000 // this is here for compliancy reasons.
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 67
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#define DRIVER_INDICATOR_LED_TOTAL 0
#endif
