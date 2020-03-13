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

// place overrides here

#define TAPPING_TERM 200

#ifdef MOUSEKEY_ENABLE
  #undef MOUSEKEY_INTERVAL
  #define MOUSEKEY_INTERVAL 5

  #undef MOUSEKEY_TIME_TO_MAX
  #define MOUSEKEY_TIME_TO_MAX 150

  #undef MOUSEKEY_MAX_SPEED
  #define MOUSEKEY_MAX_SPEED 3

  #undef MOUSEKEY_MOVE_DELTA
  #define MOUSEKEY_MOVE_DELTA 3

  #undef MOUSEKEY_DELAY
  #define MOUSEKEY_DELAY 0
#endif

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 15
// #undef BACKLIGHT_LEVELS
// #define BACKLIGHT_BREATHING
// #undef BREATHING_PERIOD
// #define BREATHING_PERIOD 4
