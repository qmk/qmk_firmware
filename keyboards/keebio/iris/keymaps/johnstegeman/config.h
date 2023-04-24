/*
Copyright 2023 John Stegeman

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

// #define USE_I2C
#define EE_HANDS

#define TAPPING_TOGGLE 1 // tap just once for TT() to toggle the layer
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

#define RGBLIGHT_LAYERS

#define RGBLIGHT_DEFAULT_HUE 85
#define RGBLIGHT_DEFAULT_SAT 255

#undef RGBLIGHT_DEFAULT_MODE
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT

#undef RGBLIGHT_EFFECT_BREATHING // fading in and out
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD // rainbow all keys at the same time
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL // rainbow top bottom
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST // red -> green -> blue
#undef RGBLIGHT_EFFECT_ALTERNATING // blinking
#undef RGBLIGHT_EFFECT_TWINKLE // randomly fading in and out single keys