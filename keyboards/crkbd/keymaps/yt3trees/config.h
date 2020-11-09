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

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

// マウス入力から反応までの遅延
#undef  MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

// マウス操作がトップスピードになるまでの時間
#undef  MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 30

// 押しっぱなしの時の反応までのインターバル
#undef  MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 0

// カーソルの移動スピード
#undef  MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 1

#undef  MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 50

#undef  MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 0

#undef  MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 1

