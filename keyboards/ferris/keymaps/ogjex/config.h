/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published bynnnn
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

#undef TAPPING_TERM
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEYS
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define QUICK_TAP_TERM 120

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 5
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA 1
#undef MOUSEKEY_INITIAL_SPEED
#define MOUSEKEY_INITIAL_SPEED 1
#undef MOUSEKEY_DECELERATED_SPEED
#define MOUSEKEY_DECELERATED_SPEED 12
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 22
#define USB_SUSPEND_WAKEUP_DELAY 0
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 83

#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 83

#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 3
