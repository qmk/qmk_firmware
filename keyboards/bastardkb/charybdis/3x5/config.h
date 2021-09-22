/*

Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>

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

#define VENDOR_ID 0xA8F8
#define PRODUCT_ID 0x1832
#define DEVICE_VER 0x0001
#define MANUFACTURER Bastard Keyboards
#define PRODUCT Charybdis Nano

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

// wiring of each half
#define MATRIX_ROW_PINS { B7, C6, D4, B5 }
#define MATRIX_COL_PINS { C7, F0, D7, E6, B4  }

#define MATRIX_ROW_PINS_RIGHT { F0, C6, D4, B5 }
#define MATRIX_COL_PINS_RIGHT { C7, B7, D7, E6, B4 }

#define DIODE_DIRECTION ROW2COL

#define ROTATIONAL_TRANSFORM_ANGLE     -25

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW             0
#define BOOTMAGIC_LITE_COLUMN          0
#define BOOTMAGIC_LITE_ROW_RIGHT       6
#define BOOTMAGIC_LITE_COLUMN_RIGHT    5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2
#define MASTER_RIGHT

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* PMW3360 Settings */
#define PMW3360_CS_PIN           B0

/* Default miryoku layers */
#define BASE  0
#define MBO   1
#define MEDIA 2
#define NAV   3
#define MOUSE 4
#define SYM   5
#define NUM   6
#define FUN   7

/* custom layer names and redo/undo copied over from miryoku */
#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used
#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO