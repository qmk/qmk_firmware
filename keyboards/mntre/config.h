// Copyright 2021 Cedric Vincent (@cdc-mkb)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 14

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
#define MATRIX_ROW_PINS { B6, B5, B4, D7, D6, D4 }
#define MATRIX_COL_PINS { D5, F7, E6, C7, B3, B2, B1, B0, F0, F1, F4, F5, F6, C6 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B7
#define BACKLIGHT_CUSTOM_RESOLUTION 0x400
#define BACKLIGHT_LIMIT_VAL 84

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

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

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0
