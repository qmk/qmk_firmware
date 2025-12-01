/*
Copyright 2021 rate

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

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

#define MATRIX_ROW_PINS { D4, C6, D7, B3, B4, B5 }
#define MATRIX_COL_PINS { E6, F0, F1, F4, F5, F6, F7, B6, D6 }

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* OLED */
#define OLED_DISPLAY_128X64

#define OLED_FONT_WIDTH 6
#define OLED_FONT_HEIGHT 6

#define OLED_UPDATE_INTERVAL 1000

#define OLED_TIMEOUT 0

#define OLED_BRIGHTNESS 255
