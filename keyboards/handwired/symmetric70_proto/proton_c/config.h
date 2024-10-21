/*
Copyright 2021 mtei

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


/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Proton-C **************************
                 ====
         +-------====------+
   DEBUG | A9/TX/SCL2   5V | (VUSB)
         | A10/RX/SDA2 GND |
         | GND       FLASH |
         | GND        3.3V | (VCC)
     C15 | B7/SDA1      A2 | C0
     C14 | B6/SCL1      A1 | C1
     C13 | B5           A0 | C2
     C12 | B4      SCL1/B8 | C3
     C11 | B3     SCLK/B13 | C4
     C10 | B2     MISO/B14 | C5
     C9  | B1     MOSI/B15 | C6
     C8  | B0      SDA1/B9 | C7
         +---+         +---+
         +---+         +---+
      R0 | A4          B10 |
      R1 | A5          B11 |
      R2 | A6          B12 |
      R3 | A7          A14 |
      R4 | A8          A13 |
         | A15         RST |
         +-----------------+
***************************************/


/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#ifdef DEBUG_CONFIG
#    define MATRIX_DEBUG_PIN A9
#    include "../debug_config.h"
#endif
