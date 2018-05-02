/*
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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define CATERINA_BOOTLOADER

#define MOUSEKEY_DELAY             32
#define MOUSEKEY_INTERVAL          16

#define MOUSEKEY_MOVE_DELTA        3
#define MOUSEKEY_MAX_SPEED         10 /* times faster than MOVE_DELTA */
#define MOUSEKEY_TIME_TO_MAX       10

#define MOUSEKEY_WHEEL_DELTA       1
#define MOUSEKEY_WHEEL_MAX_SPEED   1 /* times faster */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0

#endif
