/*
Copyright 2021 illness072

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

#    define RGBLED_SPLIT { 27, 27 }
#    define RGBLED_NUM 54 // backlight x42 + underglow x12
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 170 /* The maximum brightness level */
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

#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL
#    define RGB_MATRIX_HUE_STEP RGBLIGHT_HUE_STEP
#    define RGB_MATRIX_SAT_STEP RGBLIGHT_SAT_STEP
#    define RGB_MATRIX_VAL_STEP RGBLIGHT_VAL_STEP
#    define RGB_MATRIX_SPD_STEP 8
#endif

#ifndef OLED_FONT_H
#   define OLED_FONT_H "keyboards/elephant42/lib/glcdfont.c"
#endif
