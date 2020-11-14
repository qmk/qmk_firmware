/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL

/* Select hand configuration */

#define MASTER_LEFT
#define EE_HANDS

#define PREVENT_STUCK_MODIFIERS
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

#define TAPPING_TERM 160

// #define TAPPING_TERM 160
// #define AUTO_SHIFT_TIMEOUT 150
/* #define MOUSEKEY_INTERVAL 10 */
/* #define MOUSEKEY_TIME_TO_MAX 100 */
/* #define MOUSEKEY_MAX_SPEED 4 */
/* #define MOUSEKEY_DELAY 0 */
/* #define MOUSEKEY_WHEEL_MAX_SPEED 3 */
/* #define MOUSEKEY_WHEEL_TIME_TO_MAX 100 */

/* #undef RGB_DI_PIN */
/* #define RGB_DI_PIN B6 */
/* #undef RGBLED_NUM */
/* #define RGBLED_NUM 10 */
/* #define RGBLIGHT_TIMER */
/* #define RGBLIGHT_ANIMATIONS */
/* #define RGBLIGHT_HUE_STEP 10 */
/* #define RGBLIGHT_SAT_STEP 17 */
/* #define RGBLIGHT_VAL_STEP 17 */

#endif
