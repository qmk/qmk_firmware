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
#define VENDOR_ID       0x006a     //jels
#define PRODUCT_ID      0x000b     //Boaty
#define DEVICE_VER      0x0001
#define MANUFACTURER    jels
#define PRODUCT         boaty

/* Define Matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 11

/*Define Matrix Pins */
#define MATRIX_ROW_PINS {D6, B0, D7, B5, B3, B4, B2}
#define MATRIX_COL_PINS {B1, C0, C1, C2, D4, D1, D0, C5, C4, C3, D5}
/* ws2812 RGB LED */

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

