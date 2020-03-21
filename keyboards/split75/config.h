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
#pragma once

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
#define MANUFACTURER    Wheatfield
#define PRODUCT         Split75   

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 14

#define RGBLED_NUM 8
#define RGBLIGHT_ANIMATIONS

#define NO_UART 1
/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))
