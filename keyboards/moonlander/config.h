/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

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
// clang-format off
#define VENDOR_ID       0x3297
#define PRODUCT_ID      0x1969
#define MANUFACTURER    ZSA
#define PRODUCT         Moonlander Mark I
#define DESCRIPTION     A keyboard
#define DEVICE_VER      0x0001
#define WEBUSB_LANDING_PAGE_URL u8"configure.ergodox-ez.com"

// clang-format on

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 7

/* Planck PCB default pin-out */
// #define MATRIX_ROW_PINS { B10, B11, B12, B13, B14, B15 }
// #define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6 }

// #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }
// #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 }

// #define MCP23_LED_R GPB7
// #define MCP23_LED_G GPB6
// #define MCP23_LED_B GPA7

#define EEPROM_I2C_24LC128
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (1638-1)

// Not needed, is default address:
// #define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
#    define NO_ACTION_MACRO
#    define NO_ACTION_FUNCTION
#endif

#define I2C1_CLOCK_SPEED 400000

#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110111

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define RGB_MATRIX_CENTER \
    { 125, 26 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 175 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED true

// #define RGB_MATRIX_LED_PROCESS_LIMIT 5
// #define RGB_MATRIX_LED_FLUSH_LIMIT 26

#define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE 1

#define MOUSEKEY_INTERVAL           20
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          7
#define MOUSEKEY_WHEEL_DELAY        MOUSEKEY_DELAY
#define MOUSEKEY_WHEEL_INTERVAL     MOUSEKEY_INTERVAL
#define MOUSEKEY_WHEEL_MAX_SPEED    MOUSEKEY_MAX_SPEED
#define MOUSEKEY_WHEEL_TIME_TO_MAX  MOUSEKEY_TIME_TO_MAX

#define MUSIC_MAP


#define FIRMWARE_VERSION_SIZE 17
#define DYNAMIC_KEYMAP_EEPROM_ADDR (EECONFIG_SIZE + FIRMWARE_VERSION_SIZE)
