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
#define PRODUCT_ID 0x176B
#define DEVICE_VER 0x0010
#define MANUFACTURER jpskenn
#define PRODUCT Unison

/* key matrix size */
/* With Round-Robin matrix, set same size for both. */
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

/* key matrix pins */
/* With Round-Robin matrix, set same pins for both. */
#define MATRIX_ROW_PINS { B3, E6, F1, F5, F7, B2, F0, F4, F6, C7 }
#define MATRIX_COL_PINS { B3, E6, F1, F5, F7, B2, F0, F4, F6, C7 }
#define UNUSED_PINS

/* Rotary Encoder */
#define ENCODERS_PAD_A { B0, D2, D5, D6, B4 }
#define ENCODERS_PAD_B { B1, D3, D4, D7, B5 }
#define ENCODER_RESOLUTION 3  //the default & suggested is 4

#define DIODE_DIRECTION COL2ROW

/* Audio */
#ifdef AUDIO_ENABLE
  #define B6_AUDIO
  #define C6_AUDIO
  #define AUDIO_CLICKY
//   #define NO_MUSIC_MODE  // MIDI使わないなら、AUDIO_CLICKYとMUSIC_MODEを同時使用可能
#endif

/* RGB Lighting */
#define RGB_DI_PIN B7
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 8 // Layer Indicator(3) + Rotary Encoder(5), optional Underglow(8)
  #define RGBLIGHT_LED_MAP {1, 2, 3, 0, 4, 5, 6, 7} // Layer Indicator --> R.E. --> Under 〓実物確認
  #define RGBLIGHT_HUE_STEP 4
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
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  // #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
  // #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
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

/*
 * BOOTMAGIC
 * Left-Top key posision in matrix is (6,0).
 * NOTE: With Round-Robin matrix, (0,0) is always High(=pressed).
 */
#ifdef BOOTMAGIC_ENABLE
  #define BOOTMAGIC_LITE_ROW 6
  #define BOOTMAGIC_LITE_COLUMN 0
#endif

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

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
//#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 1
