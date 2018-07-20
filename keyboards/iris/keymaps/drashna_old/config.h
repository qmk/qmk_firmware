/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
#undef USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#ifdef RGBLIGHT_ENABLE
#undef RGBLED_NUM
#define RGBLED_NUM 16     // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1

#define RGBLIGHT_LIMIT_VAL 225
#endif // RGBLIGHT_ENABLE

#ifdef AUDIO_ENABLE
#define C6_AUDIO
#ifdef RGBLIGHT_ENABLE
#define NO_MUSIC_MODE
#endif //RGBLIGHT_ENABLE
#endif //AUDIO_ENABLE

#define QMK_ESC_OUTPUT F6 // usually COL
#define QMK_ESC_INPUT D7 // usually ROW
#define QMK_LED B0
#define QMK_SPEAKER C6

#undef PRODUCT
#ifdef KEYBOARD_iris_rev2
#define PRODUCT         Drashna Hacked Iris Rev.2
#endif

#define SHFT_LED1 5
#define SHFT_LED2 10

#define CTRL_LED1 6
#define CTRL_LED2 9

#define ALT_LED1 7
#define GUI_LED1 8

#endif
