/*
Copyright 2023 @mroukema

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

#define USERSPACE_H "mroukema.h"

#define TAPPING_TOGGLE 1
#define TAPPING_TERM 225

#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 140
#define COMBO_ONLY_FROM_LAYER 0

#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 3000

// Mouse Key Config
#define MK_KINETIC_SPEED
#define MOUSEKEY_INTERVAL 16

#undef MOUSEKEY_MAX_SPEED
// #define MOUSEKEY_MAX_SPEED 8

#define MOUSEKEY_MOVE_DELTA 10
#define MOUSEKEY_INITIAL_SPEED 140
#define MOUSEKEY_BASE_SPEED 3000
#define MOUSEKEY_DECELERATED_SPEED 800
#define MOUSEKEY_ACCELERATED_SPEED 2300

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 15

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15
