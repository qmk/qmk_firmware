/* Copyright 2021 3araht
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0xF4B5
#define DEVICE_VER   0x0001
#define MANUFACTURER 3araht
#define PRODUCT      bandominedoni

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 7

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
#define MATRIX_ROW_PINS { B5, B4, D7, F6, C6, D4 }
#define MATRIX_COL_PINS { D1, E6, F7, B1, B3, B2, D0 }
#define UNUSED_PINS

#define MASTER_RIGHT
#ifndef MASTER_RIGHT
//  SPLIT_HAND_MATRIX_GRID was initially designed to use with left hand side diode D35 mounted and not pressing K7 on the right hand side during boot. However when a USB cable is reconnected immediately, it fails. Decided to use "MASTER_RIGHT" to make it more reliable.
#   define SPLIT_HAND_MATRIX_GRID B5, D0
#endif

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6

//#define LED_NUM_LOCK_PIN B0
//#define LED_CAPS_LOCK_PIN B1
//#define LED_SCROLL_LOCK_PIN B2
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

//#define BACKLIGHT_PIN B7
//#define BACKLIGHT_LEVELS 3
//#define BACKLIGHT_BREATHING

#define RGB_DI_PIN D3
//#ifdef RGB_DI_PIN
//#    define RGBLED_NUM 16
//#    define RGBLIGHT_HUE_STEP 8
//#    define RGBLIGHT_SAT_STEP 8
//#    define RGBLIGHT_VAL_STEP 8
//#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
//#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
//#    define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
//#endif

#ifdef RGB_MATRIX_ENABLE

/* ws2812 RGB MATRIX */
#   define DRIVER_LED_TOTAL 76

 // reacts to keypresses
#   define RGB_MATRIX_KEYPRESSES

//  for all fingers used at once.
#   define LED_HITS_TO_REMEMBER 10

#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50
#   define RGB_MATRIX_STARTUP_SPD 127
// the above brighness setting has no effect on rgb_matrix_set_color().
// Use darker colors instead.
/*              RGB darker COLORS             */
#   define RGB_DARKWHITE 0x33, 0x33, 0x33
#   define RGB_DARKRED 0x33, 0x0, 0x0
#   define RGB_DARKCORAL 0x33, 0x18, 0xF
#   define RGB_DARKORANGE 0x33, 0x19, 0x0
#   define RGB_DARKGOLDENROD 0x2B, 0x21, 0x6
#   define RGB_DARKGOLD 0x33, 0x2B, 0x0
#   define RGB_DARKYELLOW 0x33, 0x33, 0x0
#   define RGB_DARKCHARTREUSE 0x19, 0x33, 0x0
#   define RGB_DARKGREEN 0x0, 0x33, 0x0
#   define RGB_DARKSPRINGGREEN 0x0, 0x33, 0x19
#   define RGB_DARKTURQUOISE 0xE, 0x16, 0x15
#   define RGB_DARKTEAL 0x0, 0x19, 0x19
#   define RGB_DARKCYAN 0x0, 0x33, 0x33
#   define RGB_DARKAZURE 0x1E, 0x31, 0x33
#   define RGB_DARKBLUE 0x0, 0x0, 0x33
#   define RGB_DARKPURPLE 0x18, 0x0, 0x33
#   define RGB_DARKMAGENTA 0x33, 0x0, 0x33
#   define RGB_DARKPINK 0x33, 0x19, 0x26

//  https://docs.qmk.fm/#/feature_rgb_matrix
//  Enable suspend mode.
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true

#   ifdef CONSOLE_ENABLE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   else
// #define ENABLE_RGB_MATRIX_ALPHAS_MODS
#       define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#       define ENABLE_RGB_MATRIX_BREATHING
#       define ENABLE_RGB_MATRIX_BAND_SAT
#       define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#       define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#       define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#       define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#       define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#       define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#       define ENABLE_RGB_MATRIX_SPLASH
#       define ENABLE_RGB_MATRIX_SOLID_SPLASH
//  RAINDROPS don't match well with layer LED indicator (oc) using rgb_matrix_set_color().
// #define ENABLE_RGB_MATRIX_RAINDROPS
// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
//  Recommendend not to use these.
#       ifndef VIA_ENABLE
#           define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#           define ENABLE_RGB_MATRIX_BAND_VAL
#           define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#           define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#           define ENABLE_RGB_MATRIX_CYCLE_ALL
#           define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#           define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#           define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#           define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#           define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#           define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#           define ENABLE_RGB_MATRIX_DUAL_BEACON
#           define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#           define ENABLE_RGB_MATRIX_HUE_BREATHING
#           define ENABLE_RGB_MATRIX_HUE_PENDULUM
#           define ENABLE_RGB_MATRIX_HUE_WAVE
#           define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#           define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#           define ENABLE_RGB_MATRIX_MULTISPLASH
#           define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#           define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#       endif
#   endif  // CONSOLE_ENABLE
#endif  // RGB_MATRIX_ENABLE

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

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

/* 2021/01/22 added to shrink firmware size */
// NO_ACTION_TAPPING -1964 bytes, however, this disables Layer mods...
// #define NO_ACTION_TAPPING
// NO_ACTION_ONESHOT -388 bytes
#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

#ifdef MIDI_ENABLE
#   define MIDI_ADVANCED
// Initial velocity value (avoid using 127 since it is used as a special number in some sound sources.)
#   define MIDI_INITIAL_VELOCITY 117
#endif  //  MIDI_ENABLE

/*
 * Encoder options
 */
#ifdef ENCODER_ENABLE
#   define ENCODERS_PAD_A { C7 }  // dummy
#   define ENCODERS_PAD_B { B7 }  // dummy
#   define ENCODERS_PAD_A_RIGHT { F5 }
#   define ENCODERS_PAD_B_RIGHT { F4 }
#   define ENCODER_RESOLUTION 4
#   define TAP_CODE_DELAY 10
#   define ENCODERS 2
#   define ENCODERS_CW_KEY  { {4, 5}, {6, 5} }
#   define ENCODERS_CCW_KEY { {3, 5}, {5, 5} }
#endif  // ENCODER_ENABLE
