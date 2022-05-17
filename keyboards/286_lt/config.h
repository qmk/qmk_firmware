 /*
 Copyright 2022

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

#define VENDOR_ID       0xA286
#define PRODUCT_ID      0xCEEB
#define DEVICE_VER      0x0001

#define MANUFACTURER    Sunny
#define PRODUCT         80-286_lt

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 11
#define MATRIX_ROW_PINS {B9, B8, B7, B6, B5, B4, B3, A15}
//#define MATRIX_COL_PINS {A0, A1, A2, A3, A4, A5, A6, A7, B0, B1, B2 }
//#define DIRECT_PINS { { B9, B8, B7, B6, B5, B4, B3, A15 }, { null, null, null, null, null, null, null, null } }
#define MATRIX_COL_PINS {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

#define UNUSED_PINS
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* indicator leds */
#define LED_NUM_LOCK_PIN B10
#define LED_CAPS_LOCK_PIN B2

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A6
#define SPI_MISO_PIN  A7

#define SN74HC595_SPI_SLAVE_SELECT_PIN A3
#define SN74HC595_LENGTH 2
#define SN74HC595_SPI_CLOCK_DIVISOR 8

#define EEPROM_SPI
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 1
#define EXTERNAL_EEPROM_BYTE_COUNT 1028
#define EXTERNAL_EEPROM_PAGE_SIZE 256
#define EXTERNAL_EEPROM_ADDRESS_SIZE 1


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG
//#define DEBUG_MATRIX_SCAN_RATE
//#define SN74HC595_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
