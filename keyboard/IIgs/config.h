/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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


/* USB Device descriptor parameter */
/* for Apple 
#define VENDOR_ID       0x05AC
#define PRODUCT_ID      0xBEE0
*/
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xBEE0
#define DEVICE_VER      0x0202
#define MANUFACTURER    t.m.k.
#define PRODUCT         Apple Desktop Bus Keyboard


/* message strings */
#define DESCRIPTION     Apple M0116/A9M0660 keyboard firmware


/* matrix size */
#define MATRIX_ROWS 11	// last row is virtual for modifier
#define MATRIX_COLS 8
/* define if matrix has ghost */
#define MATRIX_HAS_GHOST
/* Set 0 if need no debouncing */
#define DEBOUNCE    5


/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LCTRL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


/* layer switching */
#define LAYER_SWITCH_DELAY 100
#define LAYER_SEND_FN_TERM 300


/* legacy keymap support */
#define USE_LEGACY_KEYMAP


#endif
