/*
Copyright 2020 joshajohnson

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6A6A  // JJ
#define PRODUCT_ID      0x4414  // H20
#define DEVICE_VER      0x0001
#define MANUFACTURER    Josh Johnson
#define PRODUCT         Hub20

/* key matrix */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { A13, B14, A10, A0, A2, A1 }
#define MATRIX_COL_PINS { A6, A7, B7, B6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Rotary Encoder Things */
// #define ENCODER_DIRECTION_FLIP
#define ENCODERS_PAD_A { B12, A8 }
#define ENCODERS_PAD_B { B13, A9 }

#define RGB_DI_PIN B15
#define RGBLED_NUM 27
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== all animations enable ==*/
#define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #define RGBLIGHT_EFFECT_SNAKE
// #define RGBLIGHT_EFFECT_KNIGHT
// #define RGBLIGHT_EFFECT_CHRISTMAS
// #define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #define RGBLIGHT_EFFECT_RGB_TEST
// #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
// /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
// #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
// /*==== use exp() and sin() ====*/
// #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
// #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Tap delay for tap vs hold */
#define TAPPING_TERM 200

/* Slow down key press speed to ensure computer picks it up */
#define TAP_CODE_DELAY 10

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif
