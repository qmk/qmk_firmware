/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

/* Use I2C or Serial, not both */

// #define USE_SERIAL
#define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#undef RGBLED_NUM
#define RGBLED_NUM 12  // Number of LEDs
#define RGBLED_SPLIT { 6, 6 }
#define RGBLIGHT_LAYERS
#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_EFFECT_REACTIVE
#define RGBLIGHT_SPLIT

//tap dance shenanigans
#define TAPPING_TERM 200

//force n-key rollover to be enabled every boot
#define FORCE_NKRO

//some mouse keys tweaking, as it is generally too slow by default
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

////Leader key timeout
//#define LEADER_TIMEOUT 500
//#define LEADER_PER_KEY_TIMING 200

#undef PRODUCT
#define PRODUCT         "Will's Iris"
