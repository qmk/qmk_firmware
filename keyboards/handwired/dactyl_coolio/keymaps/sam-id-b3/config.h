/*
This is the c configuration file for the keymap

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

//#define DICE_ROLLER_ENABLE
//#define TRACKBALL_ENABLE

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

#define DISABLE_LEADER

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD


//#undef MOUSEKEY_MAX_SPEED
//#define MOUSEKEY_MAX_SPEED 1

//#undef MOUSEKEY_TIME_TO_MAX
//#define MOUSEKEY_TIME_TO_MAX 1