/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
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


#define MATRIX_ROW_PINS { B0, B1, B3, B4 }
#define MATRIX_COL_PINS { C4, C5, C6, C7, A4, A5, A6, A7, A3, A2, A1, A0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGB underglow */
// NOTE: for PS2AVRGB boards, underglow commands are sent via I2C to 0xB0.
#define RGBLED_NUM 5
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

#define USB_MAX_POWER_CONSUMPTION 100
