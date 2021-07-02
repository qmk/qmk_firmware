/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 mtei

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

#undef OLED_UPDATE_INTERVAL
#define OLED_UPDATE_INTERVAL 50

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

#define DISABLE_SYNC_TIMER

// Selection of RGBLIGHT MODE to use.
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING

#if defined(LED_ANIMATIONS)
#  if LED_ANIMATIONS_LEVEL > 1
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   //#define RGBLIGHT_EFFECT_SNAKE
   //#define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#  else
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   //#define RGBLIGHT_EFFECT_SNAKE
   //#define RGBLIGHT_EFFECT_KNIGHT
   //#define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#  endif
#endif

#endif /* CONFIG_USER_H */

#ifdef DEBUG_CONFIG
#  include "debug_config.h"
#endif
