/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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

--------------

Ported to QMK by Techsock <info@techsock.com>
*/

#pragma once

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0110
#define DEVICE_VER      0x0101
#define MANUFACTURER    Apple
#define PRODUCT         M0110(A)
#define DESCRIPTION     Converts M0110(A) to USB and/or BT

/* matrix size */
#define MATRIX_ROWS 14
#define MATRIX_COLS 8

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* magic key */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)) || \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL)) \
)

/* boot magic key */
#define BOOTMAGIC_KEY_SALT                      KC_M

/* ports */
#define M0110_CLOCK_PORT        PORTD
#define M0110_CLOCK_PIN         PIND
#define M0110_CLOCK_DDR         DDRD
#define M0110_CLOCK_BIT         1
#define M0110_DATA_PORT         PORTD
#define M0110_DATA_PIN          PIND
#define M0110_DATA_DDR          DDRD
#define M0110_DATA_BIT          0


