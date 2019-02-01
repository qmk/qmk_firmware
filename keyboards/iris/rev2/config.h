/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

#include QMK_KEYBOARD_CONFIG_H

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x1256
#define DEVICE_VER      0x0200
#define MANUFACTURER    Keebio
#define PRODUCT         Iris Keyboard
#define DESCRIPTION     Split 50 percent ergonomic keyboard

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D7, E6, B4, D2, D4 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define BACKLIGHT_PIN B5
#define BACKLIGHT_LEVELS 5

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLED_NUM 12    // Number of LEDs

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
// Dynamic macro starts after dynamic keymaps (35+(4*10*6*2)) = (35+480)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR 515
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 509    // 1024-DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#define DYNAMIC_KEYMAP_MACRO_COUNT 16
