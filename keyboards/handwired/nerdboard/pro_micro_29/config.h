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

#pragma once

#define DIODE_DIRECTION             COL2ROW

#define VERSION 63

#if VERSION == 61
  // version 6.1
  #define ROTATIONAL_TRANSFORM_ANGLE  -15
  #define POINTING_DEVICE_INVERT_Y
  #define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#elif VERSION == 63
  // version 6.3
  #define ROTATIONAL_TRANSFORM_ANGLE  -15
  #define POINTING_DEVICE_INVERT_Y
  #define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#else
  // version 6
  #define VERSION 6
  #define ROTATIONAL_TRANSFORM_ANGLE  -15
  #define POINTING_DEVICE_INVERT_X
  #define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#endif

#define DYNAMIC_KEYMAP_LAYER_COUNT  16
#define LAYER_STATE_16BIT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define POINTING_DEVICE_RIGHT
#define CHARYBDIS_POINTER_ACCELERATION_FACTOR 24
