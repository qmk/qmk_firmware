/*
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


/* Let's Split EH? pin-out */
#define MATRIX_ROW_PINS { B1, B3, D7, B4 }
#define MATRIX_COL_PINS { F4, F5, C6, B6, B5, D5 }

#define DIODE_DIRECTION COL2ROW

/* ws2812 RGB LED */
#define RGB_DI_PIN B2
#define RGBLED_NUM 12    // Number of LEDs (each hand)
#define RGBLED_SPLIT { 6, 6 }
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


/* Split Defines */
#define SPLIT_HAND_PIN D3

// The 'EH' has previously forced use of I2C so this default has been kept
// however users can undef to use serial
#define USE_I2C
