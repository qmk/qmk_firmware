// Copyright 2022 Keyprez (https://github.com/keyprez)
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
#define MASTER_RIGHT
#define MATRIX_ROW_PINS { F4, D3, F6, F7, B1, B3 }
#define MATRIX_COL_PINS { F5, B2, B5, D7, B4, B6, E6, D4 }
#define MATRIX_ROW_PINS_RIGHT { F4, B2, F6, F7, B1, B3 }
#define MATRIX_COL_PINS_RIGHT { F5, D3, B5, D7, B4, B6, E6, C6 }

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
