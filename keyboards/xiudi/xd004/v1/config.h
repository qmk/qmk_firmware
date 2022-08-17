/*
Copyright 2019 Sidney Bovet <sidney.bovet@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*
Note: the following configuration uses 98% of the flash memory, be
careful if you enable anything else. Also have a look at rules.mk
where some things are disabled to save space as well.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID  0x7844 // "XD"
#define PRODUCT_ID 0x0404
#define DEVICE_VER 0x0001
// Note: unsure about manufacturer
#define MANUFACTURER XIUDI
#define PRODUCT XD004 v1

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 4

/*
 * Keyboard Matrix Assignments
 *
 * On this board we have direct connection: no diodes.
 */
#define DIRECT_PINS        \
    {                      \
        { D3, D0, C4, B4 } \
    }

/* Backlight Setup */
// Looks like each backlight LED is connected to a single output, D5 is the one furtherst away from USB port
#define BACKLIGHT_PIN D5
#define BACKLIGHT_LEVELS 6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* RGB Underglow
This will not be used, as RGBLIGHT_ENABLE is set to 'no' in rules.mk
We do not have enough space in the flash for this at the moment, maybe
further optimizations can be done on that side.
*/
#define RGB_DI_PIN C6
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLED_NUM 2
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* disable action features */
// #define NO_ACTION_ONESHOT // 462 bytes <- this needs to be un-commented out if Link Time Optimization is disabled, otherwise file is too large
// The two below are implicit since we use LTO_ENABLE (in rules.mk)
