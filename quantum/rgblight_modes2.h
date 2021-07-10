/* Copyright 2016-2017 Yang Liu
 * Copyright 2021 mtei
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

#include <cpp_map.h>

#ifdef RGBLIGHT_ANIMATIONS
// for backward compatibility
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#ifdef RGBLIGHT_EFFECT_BREATHING
#    define _RGBM_DEF_BREATHING ,(BREATHING, 4, DYNAMIC)
#else
#    define _RGBM_DEF_BREATHING
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define _RGBM_DEF_RAINBOW_MOOD ,(RAINBOW_MOOD, 3, DYNAMIC)
#else
#    define _RGBM_DEF_RAINBOW_MOOD
#endif

#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define _RGBM_DEF_RAINBOW_SWIRL ,(RAINBOW_SWIRL, 6, DYNAMIC)
#else
#    define _RGBM_DEF_RAINBOW_SWIRL
#endif

#ifdef RGBLIGHT_EFFECT_SNAKE
#    define _RGBM_DEF_SNAKE ,(SNAKE, 6, DYNAMIC)
#else
#    define _RGBM_DEF_SNAKE
#endif

#ifdef RGBLIGHT_EFFECT_KNIGHT
#    define _RGBM_DEF_KNIGHT ,(KNIGHT, 3, DYNAMIC)
#else
#    define _RGBM_DEF_KNIGHT
#endif

#ifdef RGBLIGHT_EFFECT_CHRISTMAS
#    define _RGBM_DEF_CHRISTMAS ,(CHRISTMAS, 1, DYNAMIC)
#else
#    define _RGBM_DEF_CHRISTMAS
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define _RGBM_DEF_STATIC_GRADIENT ,(STATIC_GRADIENT, 10, STATIC)
#else
#    define _RGBM_DEF_STATIC_GRADIENT
#endif

#ifdef RGBLIGHT_EFFECT_RGB_TEST
#    define _RGBM_DEF_RGB_TEST ,(RGB_TEST, 1, DYNAMIC)
#else
#    define _RGBM_DEF_RGB_TEST
#endif

#ifdef RGBLIGHT_EFFECT_ALTERNATING
#    define _RGBM_DEF_ALTERNATING ,(ALTERNATING, 1, DYNAMIC)
#else
#    define _RGBM_DEF_ALTERNATING
#endif

#ifdef RGBLIGHT_EFFECT_TWINKLE
#    define _RGBM_DEF_TWINKLE ,(TWINKLE, 6, DYNAMIC)
#else
#    define _RGBM_DEF_TWINKLE
#endif

////  Add a new mode here.
// #ifdef RGBLIGHT_EFFECT_<name>
// #    define _RGBM_DEF_<name> ,(<name>, <num_of_submodes>, <STATIC|DYNAMIC>)
// #else
// #    define _RGBM_DEF_<name>
// #endif
// then append new mode into RGBLIGHT_EFECTS__LIST

#define RGBLIGHT_EFECTS__LIST (STATIC_LIGHT, 1, STATIC)   \
    _RGBM_DEF_BREATHING \
    _RGBM_DEF_RAINBOW_MOOD \
    _RGBM_DEF_RAINBOW_SWIRL \
    _RGBM_DEF_SNAKE \
    _RGBM_DEF_KNIGHT \
    _RGBM_DEF_CHRISTMAS \
    _RGBM_DEF_STATIC_GRADIENT \
    _RGBM_DEF_RGB_TEST \
    _RGBM_DEF_ALTERNATING \
    _RGBM_DEF_TWINKLE

#define _RGBLIGHT_EFFECT_MODE_DEFINE(sym, num, type) \
    , RGBLIGHT_MODE_##sym,                                       \
    RGBLIGHT_MODE_##sym##_end = RGBLIGHT_MODE_##sym + num -1
#define RGBLIGHT_EFFECT_MODE_DEFINE(x) _RGBLIGHT_EFFECT_MODE_DEFINE x

enum RGBLIGHT_EFFECT_MODE {
    RGBLIGHT_MODE_zero = 0
    MAP(RGBLIGHT_EFFECT_MODE_DEFINE, RGBLIGHT_EFECTS__LIST)
    , RGBLIGHT_MODE_last
};
