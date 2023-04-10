/*
Copyright 2020 Keybage

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


#define MATRIX_ROW_PINS { F5, B5, B6, B2, B3 }
#define MATRIX_COL_PINS { E6, B4, D7, B1 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 16
    #define RGBLIGHT_SLEEP
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
#endif

/* OLED Configuration */
#ifdef OLED_ENABLE
    #define OLED_TIMEOUT	    60000
    #define OLED_LOGO_TIMEOUT   3000  // How long (in ms) the logo appears at start up
#endif
