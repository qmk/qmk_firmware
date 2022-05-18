/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3333
#define DEVICE_VER      0x0100
#define MANUFACTURER    QMK
#define PRODUCT         Sun keyboard converter

/* matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS 8

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)) || \
    get_mods() == (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)) || \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
