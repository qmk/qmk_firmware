/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D

// TODO: share these strings with usbconfig.h
// Edit usbconfig.h to change these.
#define MANUFACTURER    winkeyless.kr
#define PRODUCT         jj40
#define DESCRIPTION     ortholinear keyboard

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15

/* PCB default pin-out */
#define MATRIX_ROW_PINS { D0, D5, B5, B7 }
#define MATRIX_COL_PINS { F1, F0, B0, C7, F4, F5, F6, F7, D4, D6, B4, D7 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

#define TAPPING_TOGGLE 3

#define NO_UART 1

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

#endif