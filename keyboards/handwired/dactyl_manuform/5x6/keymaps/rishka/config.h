/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

// handedness
#define USE_I2C
#define EE_HANDS

// tap
#define TAPPING_TOGGLE 3
#define ONESHOT_TAP_TOGGLE 3
#define PERMISSIVE_HOLD
#define TAPPING_TERM 300

// rgblight
#define WS2812_DI_PIN D3
#define RGBLED_NUM 54
#define RGBLIGHT_LIMIT_VAL 200
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
// #define RGBLIGHT_LED_MAP { 11,10,9,8,7,6,5,4,3,2,1,0,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 }
#define RGBLIGHT_SPLIT 27
