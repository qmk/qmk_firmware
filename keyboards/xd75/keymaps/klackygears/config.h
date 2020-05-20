/* Copyright 2020 klackygears
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

#undef PRODUCT
#define PRODUCT klackygears xd75 ortho keyboard

#define PERMISSIVE_HOLD
#define PREVENT_STUCK_MODIFIERS
#define TAPPING_TERM 150
#define IGNORE_MOD_TAP_INTERRUPT

// place overrides here
#undef RGBLED_NUM
#define RGBLED_NUM 44

 #define RGBLIGHT_LED_MAP {6,11,16,21,26,31,\
 42,40,41,43,\
 39,37,35,33,30,28,25,23,20,18,15,13,10,8,5,\
 3,1,0,2,\
 4,7,9,12,14,17,19,22,24,27,29,32,34,36,38}
/*middle
right
bottom
left
top
 */


#undef RGBLIGHT_ANIMATIONS // run RGB animations

#undef RGBLIGHT_HUE_STEP
#define RGBLIGHT_HUE_STEP 6 // units to step when in/decreasing hue
//#define RGBLIGHT_SAT_STEP 25 // units to step when in/decresing saturation
//#define RGBLIGHT_VAL_STEP 12 // units to step when in/decreasing value (brightness)

   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #undef RGBLIGHT_RAINBOW_SWIRL_RANGE
   #define RGBLIGHT_RAINBOW_SWIRL_RANGE 75
   #define RGBLIGHT_EFFECT_SNAKE
    #undef  RGBLIGHT_EFFECT_SNAKE_LENGTH
    #define RGBLIGHT_EFFECT_SNAKE_LENGTH 20
   #define RGBLIGHT_EFFECT_KNIGHT
    #undef  RGBLIGHT_EFFECT_KNIGHT_LENGTH
    #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 20
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
//   #define RGBLIGHT_EFFECT_BEAM
//   #define RGBLIGHT_EFFECT_HYPERBEAM
//   #define RGBLIGHT_EFFECT_RAINBOW_SPARKLE
