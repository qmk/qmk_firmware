// Copyright 2022 JoshwJB (@JoshwJB)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 4

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
#define MATRIX_ROW_PINS \
    { F6 }
#define MATRIX_COL_PINS \
    { B1, B3, B2, B6 }

/* encoder support */
#define ENCODERS_PAD_A \
    { F4 }
#define ENCODERS_PAD_B \
    { F5 }

#define ENCODER_RESOLUTION 2

#define TAP_CODE_DELAY 10

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
