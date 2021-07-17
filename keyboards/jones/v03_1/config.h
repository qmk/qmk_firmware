/*
Copyright 2020 Takeshi Nishio

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

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x175A
#define DEVICE_VER 0x0031
#define MANUFACTURER jpskenn
#define PRODUCT Jones

/* key matrix size */
// Same size for Jones' custom Round-Robin matrix.
#define MATRIX_ROWS 11
#define MATRIX_COLS 11

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
// Same pins for Jones' custom Round-Robin matrix.
#define MATRIX_ROW_PINS { D4, D7, C7, F1, F4, F5, D6, D5, E6, B0, B1 }
#define MATRIX_COL_PINS { D4, D7, C7, F1, F4, F5, D6, D5, E6, B0, B1 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
// No need to define DIODE_DIRECTION for Jones' custom Round-Robin matrix.
//#define DIODE_DIRECTION COL2ROW

/* Rotary Encoder */
#define ENCODERS_PAD_A { F6, B3 }
#define ENCODERS_PAD_B { F7, B2 }
#define ENCODER_RESOLUTION 4  //the default & suggested is 4

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN C6
  #define AUDIO_PIN_ALT B7  // 2nd pin for simultaneous audio.
  #define AUDIO_CLICKY
#endif

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
//#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

// #define BACKLIGHT_PIN B7
// #define BACKLIGHT_BREATHING
// #define BACKLIGHT_LEVELS 3

#define RGB_DI_PIN F0
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 14 // Left(4) + Right(2) + Under(8)
  #define RGBLIGHT_LED_MAP {0,1,2,3,13,12,4,5,6,7,8,9,10,11} // Left --> Right --> Under
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  // #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== Lighting Layers ==*/
  #define RGBLIGHT_LAYERS
  // #define RGBLIGHT_MAX_LAYERS 2
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
  /*== all animations enable ==*/
  // #define RGBLIGHT_ANIMATIONS
  /*== or choose animations ==*/
  // #define RGBLIGHT_EFFECT_BREATHING
  // #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  // #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
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
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is userful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

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

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
