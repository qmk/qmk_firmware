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

// when you tap then hold - setting quick tap term to 0 means you get the hold action,
// otherwise the tap to hold time must be below this to activate autorepeat.
#define QUICK_TAP_TERM 0

// permissive hold means D(a), D(b), U(b), U(a) will always emit the modified version of b,
// without this if the above is within tapping tarm you get ab instead.
#define PERMISSIVE_HOLD
// hold on other key press will mean that D(mod), D(b), U(mod), U(b) will emit the hold action on mod
//#define HOLD_ON_OTHER_KEY_PRESS

#define TAPPING_TERM 175

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000

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
    #define RGBLIGHT_DEFAULT_VAL 60
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

