/*
Copyright 2017 Damien Broqua <contact@darkou.fr>

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

    #include "config_common.h"

    /* USB Device descriptor parameter */
    #define VENDOR_ID       0xFEED
    #define PRODUCT_ID      0x6060
    #define DEVICE_VER      0x0001
    #define MANUFACTURER    DARKOU
    #define PRODUCT         DK60
    #define DESCRIPTION     QMK keyboard firmware for DK60 support

    /* key matrix size */
    #define MATRIX_ROWS 5
    #define MATRIX_COLS 13

    // ROWS: Top to bottom, COLS: Left to right
    #define MATRIX_ROW_PINS { B6, B4, D7, D6, D4 }
    #define MATRIX_COL_PINS { B0, B3, B2, B1, D3, D5, B5, B7, C6, C7, D0, D1, D2 }
    #define UNUSED_PINS

    /* COL2ROW or ROW2COL */
    #define DIODE_DIRECTION COL2ROW

    /* Set 0 if debouncing isn't needed */
    #define DEBOUNCING_DELAY 5

    /* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
    #define LOCKING_SUPPORT_ENABLE
    /* Locking resynchronize hack */
    #define LOCKING_RESYNC_ENABLE

    /* key combination for command */
    #define IS_COMMAND() ( \
        keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
    )
#endif
