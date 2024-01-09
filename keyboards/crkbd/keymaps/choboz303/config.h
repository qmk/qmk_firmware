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
#define CMD_ESC LCMD_T(KC_ESC)

#define SFT_ESC SFT_T(KC_ESC)
#define SFT_BSPC SFT_T(KC_BSPC)
#define SFT_Z SFT_T(KC_Z)
#define SFT_A SFT_T(KC_A)
#define SFT_SLSH SFT_T(KC_SLSH)
#define SFT_QUOT SFT_T(KC_QUOT)

#define CTL_SPC CTL_T(KC_SPC)
#define CTL_ENT CTL_T(KC_ENT)
#define CTL_A CTL_T(KC_A)
#define CTL_Q CTL_T(KC_Q)
#define CTL_QUOT CTL_T(KC_QUOT)

// #define MASTER_RIGHT
// #define EE_HANDS

//#define QUICK_TAP_TERM 0
// #define TAPPING_TERM 160
#define PERMISSIVE_HOLD

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
