/* Copyright 2020 Erkki Halinen & Toni Johansson
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

/* prkl30 default pinout */
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { B4, B5, F6, F5, F4, F7, B1, B3, B2, B6}
/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }
#define ENCODER_RESOLUTION 4

/* RGB Light Configuration */

#define RGB_DI_PIN D1
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
#define RGBLED_NUM 13
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
