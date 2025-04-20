/* Copyright (C) 2019, 2020  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// #include "config_common.h" // no longer required

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
//#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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

#define MATRIX_ROW_PINS { F6, F5, F4, F1 }
#define MATRIX_COL_PINS { F7, E2, C7, C6, B6, B5, D7, D6, D4, D5, D3, D2 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define LAYER_STATE_8BIT

// Configure the global tapping term (default: 200ms)
#undef TAPPING_TERM // if not default
#define TAPPING_TERM 225
#define TAPPING_TERM_PER_KEY  // reduce for HRM Shifts

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// Opposite hands rule for HRMs
#define CHORDAL_HOLD

// Default to Mac hotkeys for Select_word
#define SELECT_WORD_OS_MAC

// Don't apply custom shift keys when any non-shift mod is held.
#define CUSTOM_SHIFT_KEYS_NEGMODS ~MOD_MASK_SHIFT

#define COMBO_TERM 30        // how quickly all combo keys must be pressed in succession to trigger
// #define COMBO_TERM_PER_KEY   // reduce for combos that misfire on rolls
// #define COMBO_MUST_HOLD_MODS // if a combo triggers a modifier, only trigger when the combo is held
// #define COMBO_HOLD_TERM 200  // how long at least one of the combo keys must be held to trigger
#define COMBO_ONLY_FROM_LAYER 0 // combos mapped to base layer only
#define COMBO_STRICT_TIMER

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// Holding Shift while Caps Word is active inverts the shift state.
#define CAPS_WORD_INVERT_ON_SHIFT
// When idle, turn off Caps Word after 10 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 10000


// Auto Shift
// #define NO_AUTO_SHIFT_ALPHA
// #define AUTO_SHIFT_TIMEOUT 175 /* ms */
// #define AUTO_SHIFT_NO_SETUP
// #define RETRO_SHIFT

// Turn Layer Lock off after 60 seconds
// #define LAYER_LOCK_IDLE_TIMEOUT 60000

// Feature disable options
// These options are also useful to firmware size reduction.


/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER    // if you’re not using layers at all, you can outright remove the functionality altogether
// #define NO_ACTION_TAPPING  // tapping keys (mod tap, layer tap, etc)
// #define NO_ACTION_ONESHOT  // one-shot mods
