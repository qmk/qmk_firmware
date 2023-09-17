/*
Copyright 2017 Chuck Lauer Vose <vosechu@gmail.com>

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

#undef RGBLED_NUM
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
#define RGBLED_NUM 3
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8

#define RGBLIGHT_SLEEP // Put the keyboard to sleep when USB goes dark

#define LAYOUT_ortho_half_5x7( \
    L00, L01, L02, L03, L04, L05, L06, \
    L10, L11, L12, L13, L14, L15, L16, \
    L20, L21, L22, L23, L24, L25, L26, \
    L30, L31, L32, L33, L34, L35, L36, \
    L40, L41, L42, L43, L44, L45, L46 \
    ) \
    LAYOUT_ortho_5x14( \
        L00, L01, L02, L03, L04, L05, L06, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, \
        L10, L11, L12, L13, L14, L15, L16, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, \
        L20, L21, L22, L23, L24, L25, L26, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, \
        L30, L31, L32, L33, L34, L35, L36, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO, \
        L40, L41, L42, L43, L44, L45, L46, KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO  \
    )
