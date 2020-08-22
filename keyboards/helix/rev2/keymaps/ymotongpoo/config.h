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

// If you need more program area, try select and reduce rgblight modes to use.
#undef MASTER_LEFT
#define MASTER_RIGHT

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

#undef RGBLED_NUM
#define RGBLED_NUM 50
#define RGBLED_SPLIT {25, 25}

#define RGBLIGHT_MAX_LAYERS 32

#define LED_LAYOUT( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36 \
) { \
    L05, L04, L03, L02, L01, L00, \
    L10, L11, L12, L13, L14, L15, \
    L25, L24, L23, L22, L21, L20, \
    L30, L31, L32, L33, L34, L35, L36, \
    R00, R01, R02, R03, R04, R05, \
    R15, R14, R13, R12, R11, R10, \
    R20, R21, R22, R23, R24, R25, \
    R36, R35, R34, R33, R32, R31, R30 \
}

#define RGBLIGHT_LED_MAP LED_LAYOUT( \
   0,  1,  2,  3,  4,  5,            37, 36, 35, 34, 33, 32, \
   6,  7,  8,  9, 10, 11,            43, 42, 41, 40, 39, 38, \
  12, 13, 14, 15, 16, 17,            49, 48, 47, 46, 45, 44, \
  18, 19, 20, 21, 22, 23, 24,    56, 55, 54, 53, 52, 51, 50)
