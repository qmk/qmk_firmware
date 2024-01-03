/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLED_NUM 20
  //#define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

#ifdef ENCODER_ENABLE
  #define ENCODER_RESOLUTION 2
  #define ENCODER_DIRECTION_FLIP
#endif

/* TODO fix up
#ifdef MOUSEKEY_ENABLE
  #define MOUSEKEY_DELAY 300 // Delay between pressing a movement key and cursor movement
MOUSEKEY_INTERVAL
50
Time between cursor movements
MOUSEKEY_MAX_SPEED
10
Maximum cursor speed at which acceleration stops
MOUSEKEY_TIME_TO_MAX
20
Time until maximum cursor speed is reached
MOUSEKEY_WHEEL_DELAY
300
Delay between pressing a wheel key and wheel movement
MOUSEKEY_WHEEL_INTERVAL
100
Time between wheel movements
MOUSEKEY_WHEEL_MAX_SPEED
8
Maximum number of scroll steps per scroll action
MOUSEKEY_WHEEL_TIME_TO_MAX
40
Time until maximum scroll speed is reached
#endif
    */
