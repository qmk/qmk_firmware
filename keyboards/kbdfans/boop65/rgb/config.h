/* Copyright 2021 Dztech <moyi4681@Live.cn>
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
#define PRODUCT_ID      0x1000
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDFANS
#define PRODUCT         BOOP65RGB

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

#define USB_SUSPEND_WAKEUP_DELAY 5000

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#    define DRIVER_ADDR_1 0b0110000
#    define DRIVER_COUNT 1
#    define DRIVER_1_LED_TOTAL 83
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#    define DRIVER_INDICATOR_LED_TOTAL 0
#endif

#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2