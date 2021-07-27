/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
// clang-format off
#define VENDOR_ID       0x3297
#define PRODUCT_ID      0x1969
#define MANUFACTURER    ZSA Technology Labs
#define PRODUCT         Moonlander Mark I
#define DEVICE_VER      0x0001
#define WEBUSB_LANDING_PAGE_URL u8"configure.ergodox-ez.com"

// clang-format on

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 7

/*  PCB default pin-out */
// #define MATRIX_ROW_PINS { B10, B11, B12, B13, B14, B15 }
// #define MATRIX_COL_PINS { A0, A1, A2, A3, A6, A7, B0 }

// #define MCP23_ROW_PINS { GPB5, GBP4, GBP3, GBP2, GBP1, GBP0 }
// #define MCP23_COL_PINS { GPA0, GBA1, GBA2, GBA3, GBA4, GBA5, GBA6 }

// #define MCP23_LED_R GPB7
// #define MCP23_LED_G GPB6
// #define MCP23_LED_B GPA7

#define EEPROM_I2C_24LC128

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
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110111

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define RGB_MATRIX_CENTER { 125, 26 }
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 175
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define MUSIC_MAP

#define FIRMWARE_VERSION_SIZE 17
#define DYNAMIC_KEYMAP_EEPROM_ADDR (EECONFIG_SIZE + FIRMWARE_VERSION_SIZE)
#ifdef EEPROM_I2C
#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 16383
#    define DYNAMIC_KEYMAP_LAYER_COUNT 32
#endif

#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE
