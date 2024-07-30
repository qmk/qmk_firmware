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

//#define QUICK_TAP_TERM 0
#define TAPPING_TERM 230
#define DYNAMIC_TAPPING_TERM_INCREMENT 5

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 400
#define LEADER_NO_TIMEOUT

#define DYNAMIC_MACRO_SIZE 64

#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_W_OFFSET_UNMOD 1
#define MK_W_INTERVAL_UNMOD 80
#define MK_W_OFFSET_0 1
#define MK_W_INTERVAL_0 320
#define MK_W_OFFSET_1 1
#define MK_W_INTERVAL_1 160
#define MK_W_OFFSET_2 1
#define MK_W_INTERVAL_2 40

#ifdef RGBLIGHT_ENABLE
    #define RGB_DIGITAL_RAIN_DROPS
    #undef RGBLIGHT_EFFECT_BREATHING
    #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #undef RGBLIGHT_EFFECT_SNAKE
    #undef RGBLIGHT_EFFECT_KNIGHT
    #undef RGBLIGHT_EFFECT_CHRISTMAS
    #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
    #undef RGBLIGHT_EFFECT_RGB_TEST
    #undef RGBLIGHT_EFFECT_ALTERNATING
    #undef RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 127
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#endif