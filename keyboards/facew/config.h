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

#ifndef FACEW_CONFIG_H
#define FACEW_CONFIG_H

#include "config_common.h"

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define MANUFACTURER    NotActuallyWinkeyless
#define PRODUCT         facew

#define RGBLED_NUM 16

#define MATRIX_ROWS 8
#define MATRIX_COLS 11

#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_COL_PINS { A0, A1, A2, A3, A4, A5, A6, A7, C7, C6}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5

#define NO_BACKLIGHT_CLOCK
#define BACKLIGHT_LEVELS 1
#define RGBLIGHT_ANIMATIONS

#define NO_UART 1

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

#endif
