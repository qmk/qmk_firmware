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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#undef TAPPING_TERM
#define TAPPING_TERM 300
#define PERMISSIVE_HOLD
/* when TAPPING_TERM >= 500 same effect PERMISSIVE_HOLD.
   see tmk_core/common/action_tapping.c */

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   //#define RGBLIGHT_EFFECT_BREATHING
   //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
   //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   //#define RGBLIGHT_EFFECT_KNIGHT
   //#define RGBLIGHT_EFFECT_CHRISTMAS
   //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

/* RGB LED Conversion macro from physical array to electric array */
#define LED_LAYOUT( \
    L00, L01, L02, L03, L04, L05,       \
    L10, L11, L12, L13, L14, L15,       \
    L20, L21, L22, L23, L24, L25,       \
    L30, L31, L32, L33, L34, L35, L36,  \
    L40, L41, L42, L43, L44, L45, L46 ) \
  { \
    L05, L04, L03, L02, L01, L00,       \
    L10, L11, L12, L13, L14, L15,       \
    L25, L24, L23, L22, L21, L20,       \
    L30, L31, L32, L33, L34, L35, L36,  \
    L46, L45, L44, L43, L42, L41, L40   \
  }

#if 1
/* RGB LED logical order map */
/* Top->Bottom, Right->Left */
#define RGBLIGHT_LED_MAP LED_LAYOUT( \
  27, 22, 17, 12,  7,  2,            \
  28, 23, 18, 13,  8,  3,            \
  29, 24, 19, 14,  9,  4,            \
  30, 25, 20, 15, 10,  5,  0,        \
  31, 26, 21, 16, 11,  6,  1 )
#endif

#if 0
/* RGB LED logical order map */
/* Left->Right, Top->Bottom */
#define RGBLIGHT_LED_MAP LED_LAYOUT( \
   0,  1,  2,  3,  4,  5,            \
   6,  7,  8,  9, 10, 11,            \
  12, 13, 14, 15, 16, 17,            \
  18, 19, 20, 21, 22, 23, 24,        \
  25, 26, 27, 28, 29, 30, 31 )
#endif

#endif /* CONFIG_USER_H */
