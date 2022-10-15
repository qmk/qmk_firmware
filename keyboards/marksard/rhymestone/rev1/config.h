/*
Copyright 2020 marksard

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
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

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
#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6

// #define BACKLIGHT_PIN B7
// #define BACKLIGHT_BREATHING
// #define BACKLIGHT_LEVELS 3

#define RGB_DI_PIN D3

#ifdef RGBLIGHT_ENABLE
// #ifdef RGB_DI_PIN
  #define RGBLED_NUM 40
  #define RGBLED_SPLIT {20, 20}
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
//   #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
  /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
  #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
  /*==== use exp() and sin() ====*/
  #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
  #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

#ifdef RGB_MATRIX_ENABLE
  #define RGBLED_NUM 40    // Number of LEDs
  #define RGB_MATRIX_LED_COUNT RGBLED_NUM
  #define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
  // #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
  #define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
  // #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
  // #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10

//   #undef ENABLE_RGB_MATRIX_ALPHAS_MODS
//   #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//   #undef ENABLE_RGB_MATRIX_BREATHING
//   #undef ENABLE_RGB_MATRIX_BAND_SAT
//   #undef ENABLE_RGB_MATRIX_BAND_VAL
//   #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
//   #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//   #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
//   #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
//   #undef ENABLE_RGB_MATRIX_CYCLE_ALL
//   #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
//   #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
//   #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
//   #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//   #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//   #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
//   #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
//   #undef ENABLE_RGB_MATRIX_DUAL_BEACON
//   #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
//   #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//   #undef ENABLE_RGB_MATRIX_RAINDROPS
//   #undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//   #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
//   #undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

//   #define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

//   #undef ENABLE_RGB_MATRIX_SPLASH
//   #undef ENABLE_RGB_MATRIX_MULTISPLASH
//   #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
//   #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_TYPING_HEATMAP
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
