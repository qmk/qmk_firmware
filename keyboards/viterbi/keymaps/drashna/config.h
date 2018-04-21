/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

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

#include QMK_KEYBOARD_CONFIG_H


#ifdef RGBLIGHT_ENABLE
#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 16
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 300
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#endif // RGBLIGHT_ENABLE


#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#ifndef NO_PRINT
#define NO_PRINT
#endif // !NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#undef PRODUCT
#define PRODUCT   Drashnas Viterbi Macro Pad

#define USE_I2C

#ifdef AUDIO_ENABLE
#define C6_AUDIO
#define NO_MUSIC_MODE
#endif

#define LAYOUT_ortho_5x7( \
    L00, L01, L02, L03, L04, L05, L06, \
    L10, L11, L12, L13, L14, L15, L16, \
    L20, L21, L22, L23, L24, L25, L26, \
    L30, L31, L32, L33, L34, L35, L36, \
    L40, L41, L42, L43, L44, L45, L46 \
    ) \
    LAYOUT( \
        L00, L01, L02, L03, L04, L05, L06, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        L10, L11, L12, L13, L14, L15, L16, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        L20, L21, L22, L23, L24, L25, L26, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        L30, L31, L32, L33, L34, L35, L36, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
        L40, L41, L42, L43, L44, L45, L46, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO \
    )

#endif
