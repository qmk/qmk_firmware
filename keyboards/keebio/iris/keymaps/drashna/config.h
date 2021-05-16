/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

/* Use I2C or Serial, not both */

// #define USE_SERIAL
#define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLED_NUM 18  // Number of LEDs
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT \
        { 9, 9 }
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#    define RGBLIGHT_EFFECT_SNAKE_LENGTH 2

#    define RGBLIGHT_LIMIT_VAL 225
#endif  // RGBLIGHT_ENABLE

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN C6
#    ifdef RGBLIGHT_ENABLE
#        ifndef __arm__
#            define NO_MUSIC_MODE
#        endif
#    endif  // RGBLIGHT_ENABLE
#endif      // AUDIO_ENABLE

#if defined(KEYBOARD_keebio_iris_rev1) || defined(KEYBOARD_keebio_iris_rev2)
#    define QMK_ESC_OUTPUT F6  // usually COL
#    define QMK_ESC_INPUT D7   // usually ROW
#    define QMK_LED B0
#    define QMK_SPEAKER C6
#endif

#undef PRODUCT
#if defined(KEYBOARD_keebio_iris_rev2)
#    define PRODUCT Drashna Hacked Iris Rev 2
#elif defined(KEYBOARD_keebio_iris_rev3)
#    define PRODUCT Drashna Hacked Iris Rev 3
#elif defined(KEYBOARD_keebio_iris_rev4)
#    define PRODUCT Drashna Hacked Iris Rev 4
#endif

#define SHFT_LED1 6
#define SHFT_LED2 11

#define CTRL_LED1 7
#define CTRL_LED2 10

#define ALT_LED1 8
#define GUI_LED1 9

#define BOOTMAGIC_LITE_ROW 4
#define BOOTMAGIC_LITE_COLUMN 3
