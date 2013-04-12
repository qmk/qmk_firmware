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

#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xBB00
#define MANUFACTURER    t.m.k.
#define DEVICE_VER      0x0100
#define PRODUCT         Happy Buckling Keyboard

#define DESCRIPTION     mod version of IBM Model M keyboard

/* matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 8

/* define if matrix has ghost */
#define MATRIX_HAS_GHOST

/* Set 0 if need no debouncing */
#define DEBOUNCE    5

/* legacy keymap support */
#define USE_LEGACY_KEYMAP

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LCTRL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)) || \
    keyboard_report->mods == (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)) \
)

#endif
