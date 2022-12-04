/*
Copyright 2019 John M Daly <jmdaly@gmail.com>

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


/* ROWS: Top to bottom, COLS: Left to right
*/
#define MATRIX_ROW_PINS { A6, A5, A4, A3 }
#define MATRIX_COL_PINS { A9, A8, B15, B14, B13, A10, B9, B6, B5, B4, B3, A15 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define WS2812_SPI SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5

#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 16
#define RGB_DI_PIN A7
#define DRIVER_LED_TOTAL RGBLED_NUM

#define RGB_MATRIX_KEYPRESSES
