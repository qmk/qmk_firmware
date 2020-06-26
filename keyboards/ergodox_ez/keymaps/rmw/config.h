/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Edited like hell 2017+ by Reed Williams <rmwphd@gmail.com>

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

#define MACOSX

/* USB Device descriptor parameter */
#ifndef DESCRIPTION
#define DESCRIPTION     QMK keyboard firmware for Ergodox EZ
#endif

#define USB_MAX_POWER_CONSUMPTION 500

#define QMK_KEYS_PER_SCAN 4 
/* Set 0 if debouncing isn't needed */
#undef  DEBOUNCE
#define DEBOUNCE 5


#define ONESHOT_TIMEOUT 900 // how long before oneshot times out
//#define ONESHOT_TAP_TOGGLE 2 // how many taps before oneshot toggle is triggered

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY             20
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED         6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX       254
#undef MOUSEKEY_WHEEL_MAX_SPEED 
#define MOUSEKEY_WHEEL_MAX_SPEED   10
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 254

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
//#define DEBUG_MATRIX_SCAN_RATE
