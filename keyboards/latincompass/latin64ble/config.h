/*
Copyright 2020 latincompass

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once


#define MATRIX_ROW_PINS { D0, D1, D2, D3, D6, D7, B5, B6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7, C6 }

#define DIODE_DIRECTION ROW2COL


#define RGB_DI_PIN B7

#define RGBLED_NUM 2
#define RGB_MATRIX_LED_COUNT RGBLED_NUM

#define RGBLIGHT_VAL_STEP 25
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 20
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


#define VIA_HAS_BROKEN_KEYCODES
