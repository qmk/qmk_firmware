 /* Copyright 2022 Joah Nelson (Jels)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation,   either version 2 of the License, or
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

/* USB Device descriptor paramater */
#define VENDOR_ID       0x006A    //Jels (J)
#define PRODUCT_ID      0x0060    //Jels 60
#define DEVICE_VER      0x0001
#define MANUFACTURER    jels
#define PRODUCT         jels60

/* Define Matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/*Define Matrix Pins */
#define MATRIX_ROW_PINS {B3, D1, F0, F4, F1}
#define MATRIX_COL_PINS {E6, C7, B4, D7, D6, D4, D5, D3, F5, F6, F7, C6, B6, B5}

// Caps lock Pin
#define LED_CAPS_LOCK_PIN B7

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

