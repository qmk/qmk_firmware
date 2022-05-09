/* Copyright 2022 evan cook <evan@evancook.audio>
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
#define VENDOR_ID       0x636F
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0000
#define MANUFACTURER    evancook.audio
#define PRODUCT         sleepingdinosaur

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* key matrix pins */

#define MATRIX_ROW_PINS {D0, D1, D4, C6, D7}
#define MATRIX_COL_PINS {F4, F5, F6, F7, B1, B3}

#define UNUSED_PINS {B2, B6, B7, D5, C7, F1, F0, B4, E6}

