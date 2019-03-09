/* Copyright 2018 Josh Turner (/u/tdl-jturner)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 // additional config optoinsa vailable at https://docs.qmk.fm/reference/config-options#the-config.h-file

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// place overrides here
//#define TAPPING_TERM 200
#define TAPPING_TOGGLE 2
//#define PERMISSIVE_HOLD
//#define QMK_KEYS_PER_SCAN 4
#define FORCE_NKRO

#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

#endif
