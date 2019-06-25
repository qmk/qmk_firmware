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

/* split keyboard setup */
#define USE_SERIAL              /* SERIAL or I2C */
#define MASTER_RIGHT            /* RIGHT or LEFT (or EE_HANDS) */

#define CATERINA_BOOTLOADER     /* Use caterina bootloader to make RESET keycode available */
#define PREVENT_STUCK_MODIFIERS /* Auto-restore layer when the layer key is released */

#define MOUSEKEY_DELAY             48
#define MOUSEKEY_INTERVAL          24
#define MOUSEKEY_MOVE_DELTA        3
#define MOUSEKEY_MAX_SPEED         11 /* times faster than MOVE_DELTA */
#define MOUSEKEY_TIME_TO_MAX       10

#define MOUSEKEY_WHEEL_DELAY       72
#define MOUSEKEY_WHEEL_INTERVAL    72
#define MOUSEKEY_WHEEL_DELTA       1
#define MOUSEKEY_WHEEL_MAX_SPEED   1 /* times faster */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 1

#define MOUSEKEY_ACL_MAX_SPEED 16
#define MOUSEKEY_ACL_WHEEL_MAX_SPEED 4

#undef TAPPING_TERM
#define TAPPING_TERM 180

/* Prefer "hold" when "down -> up -> down" (recognized immediately as "tap twice" by default) */
#define TAPPING_FORCE_HOLD

/* Prefer "hold" when "SandS Dn -> A Dn -> A Up -> SandS Up" within the TAPPING_TERM */
#define PERMISSIVE_HOLD

#endif
