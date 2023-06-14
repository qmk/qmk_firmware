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

#pragma once

/* Select hand configuration */

//#define MASTER_LEFT
#define MASTER_RIGHT /* Cable connected to the right split keyboard */
// #define EE_HANDS

#define AUTO_SHIFT_TIMEOUT 210

#define TAPPING_TERM_PER_KEY

// https://beta.docs.qmk.fm/features/feature_leader_key
//#define LEADER_PER_KEY_TIMING
//#define LEADER_TIMEOUT 280

// https://docs.qmk.fm/#/feature_mouse_keys
#define MK_3_SPEED // Constant Speed Mode

#define MOUSEKEY_DELAY 300
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 3
#define MOUSEKEY_TIME_TO_MAX 60
#define MK_C_OFFSET_0    4
#define MK_C_INTERVAL_0  28
#define MK_C_OFFSET_1    8
#define MK_C_INTERVAL_1  16
#define MK_C_OFFSET_2    20
#define MK_C_INTERVAL_2  16

#define MOUSEKEY_WHEEL_MAX_SPEED 4
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

#define MK_W_OFFSET_0       1
#define MK_W_INTERVAL_0     120
#define MK_W_OFFSET_1       1
#define MK_W_INTERVAL_1     100
#define MK_W_OFFSET_2       1
#define MK_W_INTERVAL_2     60

//#define STARTUP_RESET_EEPROM // EMERGENCY

