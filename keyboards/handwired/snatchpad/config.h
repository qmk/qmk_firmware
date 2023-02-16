// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboards
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { F4, F5, F6 }
#define MATRIX_COL_PINS { B1, B3, B2 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Rotary encoder options */
#define ENCODER_RESOLUTIONS { 4, 4 }
#define ENCODERS_PAD_A { D3, D0 }
#define ENCODERS_PAD_B { D2, D1 }

//#define LED_NUM_LOCK_PIN B0
//#define LED_CAPS_LOCK_PIN B1
//#define LED_SCROLL_LOCK_PIN B2
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

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
