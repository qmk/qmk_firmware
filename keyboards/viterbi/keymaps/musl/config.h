/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

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

/******************************************************************************/
// General Configuration
/******************************************************************************/

#define USE_SERIAL
#define MASTER_LEFT

/******************************************************************************/
// Key Behavior
/******************************************************************************/

#define IGNORE_MOD_TAP_INTERRUPT
//#define LEADER_TIMEOUT 300
//#define ONESHOT_TAP_TOGGLE 2
//#define ONESHOT_TIMEOUT 300
#define PERMISSIVE_HOLD
#define PREVENT_STUCK_MODIFIERS
//#define QMK_KEYS_PER_SCAN 4
//#define RETRO_TAPPING
#define TAPPING_TERM 200
//#define TAPPING_TOGGLE 2

/******************************************************************************/
// Mouse Key Configuration
/******************************************************************************/

#define MOUSEKEY_DELAY             300
#define MOUSEKEY_INTERVAL          50
#define MOUSEKEY_MAX_SPEED         10
#define MOUSEKEY_TIME_TO_MAX       20
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

/******************************************************************************/
// LED Configuration
/******************************************************************************/

#undef RGBLED_NUM
#define RGBLED_NUM 6 // TODO: update this to match the actual number of LEDs under the board.
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 16
#define RGBLIGHT_SAT_STEP 16
#define RGBLIGHT_VAL_STEP 16

/******************************************************************************/

#endif
