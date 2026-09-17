/* Copyright 2020 marksard
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

// place overrides here

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 225

#ifdef MOUSEKEY_ENABLE
  #undef MOUSEKEY_INTERVAL
  #define MOUSEKEY_INTERVAL 1

  #undef MOUSEKEY_TIME_TO_MAX
  #define MOUSEKEY_TIME_TO_MAX 150

  #undef MOUSEKEY_MAX_SPEED
  #define MOUSEKEY_MAX_SPEED 3

  #undef MOUSEKEY_MOVE_DELTA
  #define MOUSEKEY_MOVE_DELTA 4

  #undef MOUSEKEY_DELAY
  #define MOUSEKEY_DELAY 0
#endif

// If you use the HashTwenty(alpha), please enable USE_HASHTWENTY
// #define ANGELINA_KEYMAP

// If you plug in the USB on the right side, please enable MASTER_RIGHT
// #define RHYMESTONE_RIGHTHAND
