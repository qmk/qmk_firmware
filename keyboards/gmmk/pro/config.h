/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#define DEVICE_VER 0x0001
#define VENDOR_ID 0x320F
#define PRODUCT_ID 0x5044
#define MANUFACTURER Glorious
#define PRODUCT GMMK Pro

/* key matrix size */
#define MATRIX_ROWS 11
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS \
    { B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10 }
#define MATRIX_COL_PINS \
    { A0, A1, A2, A3, A4, A8, A9, A10 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Hold ESC on start up to clear EEPROM and boot into bootloader mode */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 3

#define TAP_CODE_DELAY 10
#define ENCODERS_PAD_A \
    { C15 }
#define ENCODERS_PAD_B \
    { C14 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//#define VIAL_KEYBOARD_UID {0x81, 0xD2, 0x8A, 0x89, 0x17, 0x36, 0x53, 0x4B}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 10 }
#define VIAL_UNLOCK_COMBO_COLS { 3, 4 }
#define VIAL_ENCODER_KEYCODE_DELAY 25

/* SPI Config for LED Driver */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A6
#define SPI_MISO_PIN A7

#define DRIVER_1_CS B13
#define DRIVER_2_CS B14
#define DRIVER_1_EN C13
#define DRIVER_2_EN C13

#define DRIVER_COUNT 2

/* 1000Hz USB polling - it's the default on stock firmware */
#define USB_POLLING_INTERVAL_MS 1

/* Send up to 4 key press events per scan */
#define QMK_KEYS_PER_SCAN 4

/* Set debounce time to 5ms */
#define DEBOUNCE 5

/* Force NKRO on boot up regardless of the setting saved in the EEPROM (uncomment to enable it) */
// #define FORCE_NKRO
