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

#define TAPPING_LAYER_TERM 150 // Custom LT Tapping term
#define TAPPING_TERM_PER_KEY

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

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   //#define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   //#define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   //#define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

// LED Setting: if you have KUMO you can use RGBLIGHT_ENABLE = yes
#ifdef RGBLIGHT_ENABLE
  #define WS2812_DI_PIN B5
  #define RGBLIGHT_TIMER

  #define RGBLIGHT_LED_COUNT 6
#endif
