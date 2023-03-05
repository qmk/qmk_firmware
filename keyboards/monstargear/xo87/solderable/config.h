/* Copyright 2021 datafx
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


#define brightnessMax 8

#define MATRIX_ROW_PINS { E6,E7,E3,B0,B1,A2}
#define MATRIX_COL_PINS { C5,C3,C1,E1,D6,D2,B7,B3,F6,F7,F3,A5,A1,E2,C7,A6 }

#define KEYLED_ROWS 6
#define KEYLED_COLS 16
#define KEYLED_ROW_PINS { E5,B4,B5,F0,C6,D5 }
#define KEYLED_COL_PINS { C4,C2,C0,E0,D4,E4,B6,B2,F4,A0,F2,A4,F1,A7,D3,A3 }

#define DIODE_DIRECTION ROW2COL
#define RGB_DI_PIN D7
#define RGB_MATRIX_LED_COUNT 21
#define DRIVER_COUNT 2
#define RGBLED_NUM 21
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

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
