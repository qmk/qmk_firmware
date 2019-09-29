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
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */
#define EE_HANDS

#undef SSD1306OLED

#define USE_SERIAL_PD2

#define FORCE_NKRO

#define QMK_ESC_OUTPUT F4 // usually COL
#define QMK_ESC_INPUT D4 // usually ROW
#define QMK_LED B0

#ifdef RGBLIGHT_ENABLE
  #undef RGBLED_NUM

  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL

  #define RGBLED_NUM 27
  #define RGBLIGHT_LIMIT_VAL 120
  #define RGBLIGHT_HUE_STEP 10
  #define RGBLIGHT_SAT_STEP 16
  #define RGBLIGHT_VAL_STEP 16
  #define RGBLIGHT_SLEEP
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_MATRIX_HUE_STEP 10
#    define RGB_MATRIX_SAT_STEP 15
#    define RGB_MATRIX_VAL_STEP 16
#    define RGB_MATRIX_SPD_STEP 10
#endif

#define TAPPING_TERM 150
// #define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
// #define RETRO_TAPPING

#define TAPPING_TOGGLE 2

#define MOUSEKEY_DELAY             0
#define MOUSEKEY_INTERVAL          16
#define MOUSEKEY_MAX_SPEED         6
#define MOUSEKEY_TIME_TO_MAX       32
#define MOUSEKEY_WHEEL_MAX_SPEED   4
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

#define OLED_FONT_H "keyboards/crkbd/keymaps/rpbaptist/glcdfont.c"

#define NO_ACTION_FUNCTION
#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT

#define DISABLE_LEADER

#ifndef NO_DEBUG
  #define NO_DEBUG
#endif // !NO_DEBUG

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
  #define NO_PRINT
#endif // !NO_PRINT

#undef PRODUCT
#define PRODUCT Corne Keyboard
