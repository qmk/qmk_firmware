/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
Copyright 2021 Gary Kong <kongkm88@gmail.com> (@garykong)

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define PRODUCT         BAJJAK

/* key matrix size */
#define MATRIX_ROWS 14
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS 7

#define COL_EXPANDED { true, true, true, true, true, true, true, false, false, false, false, false, false, false }
#define MATRIX_ONBOARD_ROW_PINS { 0, 0, 0, 0, 0, 0, 0, B0,  B1,  B2,  B3,  D2,  D3,  C6 }
#define MATRIX_ONBOARD_COL_PINS { F0,  F1,  F4,  F5,  F6,  F7, D7 }
#define DIODE_DIRECTION COL2ROW
#define EXPANDER_COL_REGISTER GPIOB
#define EXPANDER_ROW_REGISTER GPIOA
#define MATRIX_EXPANDER_COL_PINS { 6, 5, 4, 3, 2, 1, 0 }
#define MATRIX_EXPANDER_ROW_PINS { 0, 1, 2, 3, 4, 5, 6 }


#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0

#define DEBOUNCE 30

#define TAPPING_TOGGLE  1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_LO       15
#endif
#ifndef LED_BRIGHTNESS_HI
#define LED_BRIGHTNESS_HI       255
#endif
#define LED_BRIGHTNESS_DEFAULT (LED_BRIGHTNESS_HI)

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER

/*
 * The debounce filtering reports a key/switch change directly,
 * without any extra delay. After that the debounce logic will filter
 * all further changes, until the key/switch reports the same state for
 * the given count of scans.
 * So a perfect switch will get a short debounce period and
 * a bad key will get a much longer debounce period.
 * The result is an adaptive debouncing period for each switch.
 *
 * If you don't define it here, the matrix code will default to
 * 5, which is now closer to 10ms, but still plenty according to
 * manufacturer specs.
 */

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define DEBUG_MATRIX_SCAN_RATE
