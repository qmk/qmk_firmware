/*
Copyright 2021 klackygears

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

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

#define MATRIX_ROW_PINS { F1, F2, F3, F4 }
#define MATRIX_COL_PINS { A3, A2, A1, A0, F6, F5, F0, E0, E1, C0, C1, C2, C3 }

#define DIODE_DIRECTION COL2ROW

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B0, C5 }
#    define ENCODERS_PAD_B { E3, C4 }
#    define ENCODER_RESOLUTIONS { 4, 4 }
#endif

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 450000
#    define OLED_FONT_H  "keyboards/ein_60/glcdfont.c"
#endif

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN C6
#    define AUDIO_CLICKY
#    define AUDIO_DAC_SAMPLE_MAX 4095U
#endif

#define RGB_DI_PIN E7
#ifdef RGB_DI_PIN
#    define RGBLED_NUM         38
#    define RGBLIGHT_HUE_STEP  4
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 200 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
// /*== customize breathing effect ==*/
//   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//   #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//   /*==== use exp() and sin() ====*/
//   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT              38
#    define RGB_MATRIX_LED_FLUSH_LIMIT    16
#    define RGB_MATRIX_DEFAULT_VAL        150
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
