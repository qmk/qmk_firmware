/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

// because layouts seem to not be respecting config.h order atm
#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_ANIMATIONS
#    if defined(__AVR__) && (!defined(__AVR_AT90USB1286__) && !defined(RGBLIGHT_ALL_ANIMATIONS))
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_SNAKE
#        define RGBLIGHT_EFFECT_KNIGHT
#    else
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_RAINBOW_MOOD
#        define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#        define RGBLIGHT_EFFECT_SNAKE
#        define RGBLIGHT_EFFECT_KNIGHT
#        if defined(RGBLIGHT_ALL_ANIMATIONS)
#            define RGBLIGHT_EFFECT_CHRISTMAS
#            define RGBLIGHT_EFFECT_STATIC_GRADIENT
#            define RGBLIGHT_EFFECT_RGB_TEST
#            define RGBLIGHT_EFFECT_ALTERNATING
#        endif
#        define RGBLIGHT_EFFECT_TWINKLE
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
#    ifndef RGB_MATRIX_REST_MODE
#        if defined(SPLIT_KEYBOARD) || defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_moonlander)
#            define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        else
#            define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN
#        endif
#    endif
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_REST_MODE
#endif

#ifdef QMK_KEYS_PER_SCAN
#    undef QMK_KEYS_PER_SCAN
#endif
#define QMK_KEYS_PER_SCAN 4

#ifdef MOUSEKEY_ENABLE
// mouse movement config
#    ifdef MK_3_SPEED
#        undef MK_3_SPEED
#    endif
#    define MK_KINETIC_SPEED
#    ifdef MK_KINETIC_SPEED
#        ifndef MOUSEKEY_DELAY
#            define MOUSEKEY_DELAY 8
#        endif
#        ifndef MOUSEKEY_INTERVAL
#            define MOUSEKEY_INTERVAL 20
#        endif
#        ifndef MOUSEKEY_MOVE_DELTA
#            define MOUSEKEY_MOVE_DELTA 25
#        endif
#    else
#        ifndef MOUSEKEY_DELAY
#            define MOUSEKEY_DELAY 300
#        endif
#        ifndef MOUSEKEY_INTERVAL
#            define MOUSEKEY_INTERVAL 50
#        endif
#        ifndef MOUSEKEY_MOVE_DELTA
#            define MOUSEKEY_MOVE_DELTA 5
#        endif
#    endif
#    ifndef MOUSEKEY_MAX_SPEED
#        define MOUSEKEY_MAX_SPEED 7
#    endif
#    ifndef MOUSEKEY_TIME_TO_MAX
#        define MOUSEKEY_TIME_TO_MAX 60
#    endif
#    ifndef MOUSEKEY_INITIAL_SPEED
#        define MOUSEKEY_INITIAL_SPEED 100
#    endif
#    ifndef MOUSEKEY_BASE_SPEED
#        define MOUSEKEY_BASE_SPEED 1000
#    endif
#    ifndef MOUSEKEY_DECELERATED_SPEED
#        define MOUSEKEY_DECELERATED_SPEED 400
#    endif
#    ifndef MOUSEKEY_ACCELERATED_SPEED
#        define MOUSEKEY_ACCELERATED_SPEED 3000
#    endif
// mouse scroll config
#    ifndef MOUSEKEY_WHEEL_DELAY
#        define MOUSEKEY_WHEEL_DELAY 15
#    endif
#    ifndef MOUSEKEY_WHEEL_DELTA
#        define MOUSEKEY_WHEEL_DELTA 1
#    endif
#    ifndef MOUSEKEY_WHEEL_INTERVAL
#        define MOUSEKEY_WHEEL_INTERVAL 50
#    endif
#    ifndef MOUSEKEY_WHEEL_MAX_SPEED
#        define MOUSEKEY_WHEEL_MAX_SPEED 8
#    endif
#    ifndef MOUSEKEY_WHEEL_TIME_TO_MAX
#        define MOUSEKEY_WHEEL_TIME_TO_MAX 80
#    endif
// mouse scroll kinetic config
#    ifndef MOUSEKEY_WHEEL_INITIAL_MOVEMENTS
#        define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 8
#    endif
#    ifndef MOUSEKEY_WHEEL_BASE_MOVEMENTS
#        define MOUSEKEY_WHEEL_BASE_MOVEMENTS 48
#    endif
#    ifndef MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS
#        define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
#    endif
#    ifndef MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS
#        define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8
#    endif
#endif  // MOUSEKEY_ENABLE

#if !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_16BIT
#endif
#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#    define DYNAMIC_KEYMAP_LAYER_COUNT 11
#endif
