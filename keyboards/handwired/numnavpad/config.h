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

#ifndef NUMNAVPAD_CONFIG_H
#define NUMNAVPAD_CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1308
#define DEVICE_VER      0x0001
#define MANUFACTURER    Myself
#define PRODUCT         numnavpad
#define DESCRIPTION     An ortholinear, split, 3D-curved keyboard with thumb clusters.

#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 5
#define MATRIX_COLS 7
#define COL_EXPANDED { true, true, true, true, false, false, false, false, false, false}
#define MATRIX_ONBOARD_ROW_PINS { F4, F5, B7, F6, F7 }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, D4, C6, D7 }
#define EXPANDER_COL_REGISTER 0
#define MATRIX_EXPANDER_COL_PINS {0, 1, 2, 3}
#define MATRIX_EXPANDER_ROW_PINS {0, 1, 2, 3, 4}

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    15

#define USB_MAX_POWER_CONSUMPTION 500

#endif
