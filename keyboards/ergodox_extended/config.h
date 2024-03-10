// Copyright 2024 Adam Coleman (@Gephorian)
// SPDX-License-Identifier: GPL-2.0-or-later

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

#pragma once

/* key matrix size */
#define MATRIX_COLS 7
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_ROWS 14

#define COL_EXPANDED { true, true, true, true, true, true, true, false, false, false, false, false, false, false }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, 0, 0, 0, B0, B1, B2, B3, D2, D3, C6 }
#define MATRIX_ONBOARD_ROW_PINS { F0, F1, F4, F5, F6, F7, D7 }
#define DIODE_DIRECTION ROW2COL
#define EXPANDER_COL_REGISTER GPIOA
#define EXPANDER_ROW_REGISTER GPIOB
#define MATRIX_EXPANDER_COL_PINS { 6, 5, 4, 3, 2, 1, 0 }
#define MATRIX_EXPANDER_ROW_PINS { 0, 1, 2, 3, 4, 5, 6 }

#define MOUSEKEY_INTERVAL           20
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          7
#define MOUSEKEY_WHEEL_DELAY        400
#define MOUSEKEY_WHEEL_INTERVAL     MOUSEKEY_INTERVAL
#define MOUSEKEY_WHEEL_MAX_SPEED    MOUSEKEY_MAX_SPEED
#define MOUSEKEY_WHEEL_TIME_TO_MAX  MOUSEKEY_TIME_TO_MAX

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)
