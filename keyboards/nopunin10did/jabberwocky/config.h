/* Copyright 2021 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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
#define VENDOR_ID           0x4E50  // "NP"
#define PRODUCT_ID          0x4A57  // "JW"
#define DEVICE_VER          0x0001
#define PRODUCT             Jabberwocky

/* key matrix size */
#define MATRIX_ROWS         12
#define MATRIX_COLS         10

/* key matrix pins */
#define MATRIX_ROW_PINS     { E6, B4, B5, B7, D5, C7, F1, F0, B1, B3, B2, B6 }
#define MATRIX_COL_PINS     { F4, F5, F6, F7, D7, C6, D4, D0, D2, D3 }
#define UNUSED_PINS

/* Indicator LEDs */
#define LED_NUM_LOCK_PIN    D1
#define LED_CAPS_LOCK_PIN   B0

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION     COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE            5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Reducing layer count to 3 for via support */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
