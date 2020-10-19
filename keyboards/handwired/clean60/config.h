/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2017 Erin Call <hello@erincall.com>

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

#ifndef CLEAN60_CONFIG_H
#define CLEAN60_CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1308
#define DEVICE_VER      0x0001
#define MANUFACTURER    hyp3r
#define PRODUCT         Clean60
#define DESCRIPTION     Some shitty handwire

#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define COL_EXPANDED { false, false, false, false, false, false, false, false, true, true, true, true, true, true }
#define MATRIX_ONBOARD_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_ONBOARD_COL_PINS { B5, F4, F5, F6, F7, B1, B3, B2, 0, 0, 0, 0, 0, 0 }
#define EXPANDER_COL_REGISTER GPIOA
#define EXPANDER_ROW_REGISTER GPIOB
#define MATRIX_EXPANDER_COL_PINS {0, 1, 2, 3, 4, 5, 6}
#define MATRIX_EXPANDER_ROW_PINS {0, 1, 2, 3, 4}

#define MOUSEKEY_INTERVAL     20
#define MOUSEKEY_DELAY        0
#define MOUSEKEY_TIME_TO_MAX  60
#define MOUSEKEY_MAX_SPEED    7
#define MOUSEKEY_WHEEL_DELAY  0

#define TAPPING_TOGGLE  1

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    15

#define USB_MAX_POWER_CONSUMPTION 500

#endif
