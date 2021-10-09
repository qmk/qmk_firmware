/* Copyright 2018 Jason Williams (Wilba)
 * Copyright 2021 Harrison Chan (Xelus)
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
#define VENDOR_ID       0x5845 // XE
#define PRODUCT_ID      0x4C50 // LP
#define DEVICE_VER      0x0001
#define MANUFACTURER    AEBoards
#define PRODUCT         AEBoards Constellation Rev1

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B1, F0, F4, F5 }
#define MATRIX_COL_PINS { E6, D5, B2, B3, D3, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// RGB Matrix
// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN F1
// The number of LEDs connected
#define DRIVER_LED_TOTAL 32

#define RGB_MATRIX_STARTUP_VAL 80
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180

#define FORCE_NKRO
