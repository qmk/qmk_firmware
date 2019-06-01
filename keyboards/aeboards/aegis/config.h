/* Copyright 2018 Jason Williams (Wilba)
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
#define VENDOR_ID       0x4145 // "AE"
#define PRODUCT_ID      0x0807 // 1800 -> 0x0708 -> 0x0807 ;-)
#define DEVICE_VER      0x0001
#define MANUFACTURER    AEboards
#define PRODUCT         Aegis
#define DESCRIPTION     1800 Left Handed Keyboard

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 9

/* key matrix pins */
#define MATRIX_ROW_PINS { F5, F6, E6, F7, D1, D0, D6, D4, B4, D7, B6, B5 }
#define MATRIX_COL_PINS { C7, C6, B7, D2, D3, B3, B2, B1, B0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//#define WT_MONO_BACKLIGHT

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM usage

// TODO: refactor with new user EEPROM code (coming soon)
#define EEPROM_MAGIC 0x451F
#define EEPROM_MAGIC_ADDR 32
// Bump this every time we change what we store
// This will automatically reset the EEPROM with defaults
// and avoid loading invalid data from the EEPROM
#define EEPROM_VERSION 0x08
#define EEPROM_VERSION_ADDR 34

// Dynamic keymap starts after EEPROM version
#define DYNAMIC_KEYMAP_EEPROM_ADDR 35
// Dynamic macro starts after dynamic keymaps (35+(4*12*9*2)) = (35+864)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 899
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 125
#define DYNAMIC_KEYMAP_MACRO_COUNT 16

