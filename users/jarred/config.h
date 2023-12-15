/* Copyright 2018 Jarred Steenvoorden
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

#pragma once

// Sets good default for the speed of the mouse.
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED

#define MOUSEKEY_INTERVAL       16
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    40
#define MOUSEKEY_MAX_SPEED      5

#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#undef MOUSEKEY_WHEEL_DELAY

#define MOUSEKEY_WHEEL_MAX_SPEED    4
#define MOUSEKEY_WHEEL_TIME_TO_MAX  255
#define MOUSEKEY_WHEEL_DELAY        0

#undef TAPPING_TOGGLE
#undef TAPPING_TERM

#define PERMISSIVE_HOLD
#define TAPPING_TOGGLE  1
#define TAPPING_TERM    200

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MACRO_TIMER 5
