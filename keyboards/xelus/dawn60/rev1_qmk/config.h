/* Copyright 2017 Jason Williams (Wilba)
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

// USB Device descriptor parameter
#define VENDOR_ID       0x5845 // XE
#define PRODUCT_ID      0x0060 // Dawn60
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Dawn60

// key matrix size
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//underglow
#define MATRIX_ROW_PINS { B1, B3, F1, F6, F7 }
#define MATRIX_COL_PINS { B0, D5, B2, F5, D3, D2, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW

// Set 0 if debouncing isn't needed
#define DEBOUNCE 5

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

//RGB Underglow defines
#define RGB_DI_PIN F0
#define WS2812_LED_TOTAL 20

//RGB Matrix defines
#define DRIVER_ADDR_1 0x74
#define DRIVER_ADDR_2 0x76

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 32
#define ISSI_DRIVER_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL + WS2812_LED_TOTAL)

#define RGB_MATRIX_STARTUP_VAL 80
#define RGB_MATRIX_KEYPRESSES

// enable/disable LEDs based on layout
// switch between split backspace (1) or normal backspace(0)
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 1
// switch between Tsangan (1) or Arrows Bottom Row (0)
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 0
// switch between standard split rshift (0) or arrows r shift (1)
// .------------------.           .-------------------.
// | ? |  Shift  | Fn |    vs     |  Shift  | Up | Fn |
// `------------------'           `-------------------'
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 1
