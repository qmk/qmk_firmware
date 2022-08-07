/*
Copyright 2019 Adam Newbold <adam@neatnik.net>

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    Apple Inc.
#define PRODUCT         Numeric Keypad IIe

/*

Pin Mappings
============

Dsub-15 Connection
------------------

          Dsub-15 (female)
    ,-------------------------.
    \ 08 07 06 05 04 03 02 01 /
     \ 15 14 13 12 11 10 09  /
      `---------------------'

Header Pins
-----------
 _____________________________________
|                                     |
|  11  10  9  8  7  6  5  4  3  2  1  |
|_____________________________________|


Header / Matrix
---------------

Pin             Name        Description
--------------------------------------------------------------
1,2,5,3,4,6     Y0-Y5       Y-direction key-matrix connections
7               NC
9,11,10,8       X4-X7       X-direction key-matrix connections


Microcontroller Configuration
-----------------------------

(Pins are for an Arduino Micro)

+-----------------------------------+
| Dsub-15 | Header | Matrix | Micro |
|---------+--------+--------+-------|
|   12    |   11   |   X5   |   B0  |
|   11    |   10   |   X6   |   D3  |
|   10    |    9   |   X4   |   B2  |
|    9    |    8   |   X7   |   D2  |
|   NC    |    7   |   NC   |   --  |
|    7    |    6   |   Y5   |   E6  |
|    6    |    5   |   Y2   |   D4  |
|    5    |    4   |   Y4   |   D7  |
|    3    |    3   |   Y3   |   C6  |
|    2    |    2   |   Y1   |   D0  |
|    1    |    1   |   Y0   |   D1  |
+-----------------------------------+

Note: Dsub-15 pins 4, 8, 13, 14, and 15 are unused

Reference
---------

https://deskthority.net/wiki/Apple_Numeric_Keypad_IIe
https://geekhack.org/index.php?topic=78048.0
http://wiki.apple2.org/index.php?title=Pinouts#Apple_.2F.2Fe_Numeric_Keypad_connector

*/

#define MATRIX_ROWS 4
#define MATRIX_COLS 6
#define MATRIX_ROW_PINS { B0, B2, D2, D3 }
#define MATRIX_COL_PINS { D1, D0, D4, C6, D7, E6 }
#define DIODE_DIRECTION COL2ROW
#define SOFT_SERIAL_PIN D0
#define DEBOUNCE 5
