// Copyright 2023 Justin (@Justin-sandwich)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 13

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

/* Key matrix pins */
//                  ROWS: 1     2     3     4     5     6     7     8
//#define MATRIX_ROW_PINS { GP12, GP13, GP14, GP15, GP16, GP21, GP23, GP20 }
//                  COLS: 1    2    3    4    5    6    7    8    9     10    11    12    13
//#define MATRIX_COL_PINS { GP9, GP8, GP7, GP6, GP5, GP4, GP3, GP2, GP22, GP26, GP27, GP28, GP29 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
//#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed (5 is default) */
#define DEBOUNCE 5

/* The 6746 has no diodes */
#define MATRIX_HAS_GHOST

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
