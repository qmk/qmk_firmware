/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Pllllllljublic License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MASTER_LEFT
#define SPLIT_TRANSPORT_MIRROR
// #define FORCED_SYNC_THROTTLE_MS 20

#define TAPPING_TOGGLE 2

#define RGBLIGHT_SPLIT
#undef RGBLED_NUM
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#define RGBLIGHT_EFFECT_BREATHING


#define RGBLIGHT_EFFECT_STATIC_GRADIENT


#define RGBLED_NUM 13
#define RGBLIGHT_LED_MAP \
    { 0, 1, 2, 3, 4, 5, 8, 7, 6, 9, 10, 11, 12 }
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8

//#define IS_LEFT 1
#define IS_RIGHT 1

#ifdef OLED_FONT_H
#    undef OLED_FONT_H
#endif
#define OLED_FONT_H "navi_font.c"

#undef OLED_FONT_END
#define OLED_FONT_END 125

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define DISABLE_LEADER

#ifndef NO_DEBUG
#    define NO_DEBUG
#endif
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#    define NO_PRINT
#endif 
