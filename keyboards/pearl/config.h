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

#ifndef PEARL_CONFIG_H
#define PEARL_CONFIG_H

#include "config_common.h"

#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0348
#define MANUFACTURER Pearl Boards
#define PRODUCT      Pearl
#define DESCRIPTION  40% keyboard

#define NO_UART 1

#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12

#define BACKLIGHT_LEVELS 1

#define MATRIX_ROWS 4
#define MATRIX_COLS 13

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

#endif
