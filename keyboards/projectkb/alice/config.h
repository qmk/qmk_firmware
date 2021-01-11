/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0159
#define PRODUCT_ID      0xA71C
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
#define MANUFACTURER ProjectKB
#define PRODUCT Alice
#define DESCRIPTION ProjectKB Alice

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { B2, B10, B11, A9, A15, B3, B4, B5, B6, B7, B8, B9, C13, C14, C15, B12 }
#define MATRIX_ROW_PINS { B1, B0, A7, A5, A4 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGBLIGHT_ANIMATIONS

#define WS2812_LED_N 14
#define RGBLED_NUM WS2812_LED_N
#define PORT_WS2812     GPIOB
#define PIN_WS2812      15
#define WS2812_SPI SPID2


// EEPROM usage
// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 32
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x01
#define EEPROM_VERSION_ADDR 34

#define EEPROM_CUSTOM_BACKLIGHT 804

#undef EEPROM_MAGIC_ADDR
#define EEPROM_MAGIC_ADDR 34
#undef EEPROM_VERSION_ADDR
#define EEPROM_VERSION_ADDR 36
#undef RGB_BACKLIGHT_CONFIG_EEPROM_ADDR
#define RGB_BACKLIGHT_CONFIG_EEPROM_ADDR 37
#undef DYNAMIC_KEYMAP_EEPROM_ADDR 
#define DYNAMIC_KEYMAP_EEPROM_ADDR 68
#undef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 66

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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
