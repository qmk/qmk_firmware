/*
Copyright 2020-2021 mtei

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

/* Pro Micro **************************
                 ====
         +-------====------+
  MDEBUG | D3/TXO      RAW |
         | D2/RXI      GND |
         | GND         RST |
         | GND         Vcc |
         | D1/SDA       F4 | COL_0_1_L
         | D0/SCL       F5 | COL_2_3_L
   ROW_0 | D4           F6 | COL_4_5_L
   ROW_1 | C6           F7 | COL_6_7_L
   ROW_2 | D7       SCK/B1 | COL_6_7_R
   ROW_3 | E6      MISO/B3 | COL_4_5_R
   ROW_4 | B4      MOSI/B2 | COL_2_3_R
  SEL_AB | B5           B6 | COL_0_1_R
        +-----------------+
***************************************/


/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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
#    define MATRIX_DEBUG_PIN D3
#    include "../debug_config.h"
#endif
