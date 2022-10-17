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

// for the following options look at https://precondition.github.io/home-row-mods

// use tapping term to decide when to apply the modifier rather than the next keypress.
// This stops rolling [D(a), D(b), U(a), U(b)] from triggering the modified version
#define IGNORE_MOD_TAP_INTERRUPT

// the following removes auto repeat on keys, but allows a key to be tapped then immediately
// held to activate the modifier.  (without this tap and hold would autorepeat)
#define TAPPING_FORCE_HOLD

// permissive hold means D(a), D(b), U(b), U(a) will always emit the modified version of b,
// without this if the above is within tapping tarm you get ab instead.
#define PERMISSIVE_HOLD
#define TAPPING_TERM 175

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 2500

// Turn off Caps Word after 5 seconds.
//#define CAPS_WORD_IDLE_TIMEOUT 5000

// disable macro / functions as we are not using them and they are not compatible with
// LTO (link time optimization)
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifdef RGBLIGHT_ENABLE
    // enable light change on layer change
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_SPLIT
    
    // increase the number of light layers
    #define RGBLIGHT_MAX_LAYERS 16

    #define RGBLIGHT_LAYER_BLINK
    #define SPLIT_LAYER_STATE_ENABLE

    // turn off unused lighting effects
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
    #undef RGBLIGHT_EFFECT_TWINKLE

    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

