/*
Copyright 2022 Gondolindrim <gondolindrim@acheronproject.com>

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
#define RGBLIGHT_DEFAULT_VAL 0 // Turned off by default

//#define ALL_RGBS // Define the RGB option here
//#define LINE_RGBS
//#define RUNE_RGBS
#define LUKE_RGBS

#define RGBLIGHT_LED_MAP {16 , 0  , 1  , 2  , 3  , 17 , 19 , 15 , 4  , 5  , 6  , 7  , 8  ,  9 , 10 , 18 , 11 , 12 , 13 , 14 , 20}
//                        D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D58, D59, D60, D61, D62, D63, D64, D65, D66, D67

#ifdef RUNE_RGBS
#       undef RGBLIGHT_LED_MAP
#       define RGBLIGHT_LED_MAP {1  , 6  , 7  , 8  , 9  , 2  , 5  , 0  , 10 , 11 , 12 , 13 , 14 , 15 , 16  , 3  , 4 , 17 , 18 , 19 , 20 }
//                               D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D58, D59, D60, D61, D62, D63, D64, D65, D66, D67
#endif

#ifdef LUKE_RGBS
#       undef RGBLIGHT_LED_MAP
#       define RGBLIGHT_LED_MAP {20 , 2  , 3  , 4  , 5  , 1  , 19 , 0  , 6  , 7  , 8  ,  9 , 10 , 11 , 12 , 18 , 13 , 14 , 15 , 16 , 17 }
//                               D18, D19, D20, D21, D22, D23, D24, D25, D26, D27, D28, D58, D59, D60, D61, D62, D63, D64, D65, D66, D67
#endif

#define RGBLIGHT_DEFAULT_VAL 0
