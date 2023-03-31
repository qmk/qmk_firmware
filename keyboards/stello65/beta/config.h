// Copyright 2021 @wekey (@@wekey)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


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
#define MATRIX_ROW_PINS { F0, E6, D0, D1, C6, F7, F6, F5, F4, F1 }
#define MATRIX_COL_PINS { C7, B6, B5, B4, D7, D6, D4, D5 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_CW_KEY  { { 4, 7 } }
#define ENCODERS_CCW_KEY { { 4, 6 } }

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
