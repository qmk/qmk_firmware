
/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Art Ortenburger

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

/* key combination for magic key command */
#undef IS_COMMAND
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LALT)) \
)

//#ifdef RGBLIGHT_ENABLE
//#define RGB_DI_PIN D3
//#define RGBLED_NUM 16     // Number of LEDs
//#define RGBLED_SPLIT { 8, 8 }
//
//#define RGBLIGHT_HUE_STEP 12
//#define RGBLIGHT_SAT_STEP 12
//#define RGBLIGHT_VAL_STEP 12
//#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
//#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
//#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
//#endif // RGBLIGHT_ENABLE

