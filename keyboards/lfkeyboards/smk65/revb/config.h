/*
Copyright 2020 LFKeyboards
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


// RevA
// #define DIODE_DIRECTION COL2ROW
// #define MATRIX_ROW_PINS {B7, F7, F6, F5, F4}
// #define MATRIX_COL_PINS {F0, F1, D2, D3, D5, D4, D6, D7, B4, B5, B6, C7, B3, B2, B1, B0}

// RevB
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS {D6, D7, E0, C3, C4}
#define MATRIX_COL_PINS {F2, C5, E5, E4, B7, B6, B5, B4, B3, B2, B1, B0, E1, C0, C1, C2}
#define RGBLED_NUM 20     // Number of LEDs

//RevB only:

#define AUDIO_VOICES
#define AUDIO_PIN C6

#define BACKLIGHT_PWM_MAP {8, 16, 40, 55, 70, 128, 200, 255}

#define RGB_DI_PIN C7  // Have to set it to something to get the ws2812 code to compile
#define RGBLED_NUM 20     // Number of LEDs
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
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
