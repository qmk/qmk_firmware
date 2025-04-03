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
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_COUNT 30
#define COMBO_TERM 30 
#define DOUBLE_TAP_S
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define COMBO_SHOULD_TRIGGER
#define MOUSEKEY_WHEEL_INTERVAL 40
#define MOUSEKEY_MOVE_DELTA 4

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 800  /* Time (in ms) before the one shot key is released */

#define SMTD_GLOBAL_TAP_TERM 220
#define SMTD_GLOBAL_FOLLOWING_TAP_TERM 200
#define SMTD_GLOBAL_SEQUENCE_TERM 100
#define SMTD_GLOBAL_RELEASE_TERM 50
// config.h
// #define CAPS_WORD_IDLgcc E_TIMEOUT 0       // Disable auto-timeout (ZMK default)
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

#define TAPPING_TERM 200
//#define QUICK_TAP_TERM
//#define TAPPING_TERM 100
#define MAX_DEFERRED_EXECUTORS 10
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


