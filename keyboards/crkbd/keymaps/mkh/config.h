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

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200

#define TAPPING_TERM_PER_KEY

// Home row mods - QWERTY
#define HMQ_A LGUI_T(KC_A)
#define HMQ_S LALT_T(KC_S)
#define HMQ_D LCTL_T(KC_D)
#define HMQ_F LSFT_T(KC_F)
#define HMQ_J RSFT_T(KC_J)
#define HMQ_K RCTL_T(KC_K)
#define HMQ_L RALT_T(KC_L)
#define HMQ_QUOT RGUI_T(KC_QUOT)

// Home row mods - Colemak-DH
#define HMC_A LGUI_T(KC_A)
#define HMC_R LALT_T(KC_R)
#define HMC_S LCTL_T(KC_S)
#define HMC_T LSFT_T(KC_T)
#define HMC_N RSFT_T(KC_N)
#define HMC_E RCTL_T(KC_E)
#define HMC_I RALT_T(KC_I)
#define HMC_O RGUI_T(KC_O)

// Thumb combos - Left hand
#define MED_ESC LT(_MEDIA,KC_ESC)
#define NAV_BSPC LT(_NAV, KC_BSPC)
#define MOU_TAB LT(_MOUSE, KC_TAB)
// Thumb combos - Right hand
#define SYM_ENT LT(_SYM, KC_ENT)
#define NUM_SPC LT(_NUM, KC_SPC)
#define FUN_DEL LT(_FUN, KC_DEL)

// Macros for copy/paste/cut/undo/redos
#define U_UND LCTL(KC_Z) // Undo
#define U_CUT LCTL(KC_X) // Cut
#define U_CPY LCTL(KC_C) // Copy
#define U_PST LCTL(KC_V) // Paste
#define U_RDO LCTL(KC_Y) // Redo




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
