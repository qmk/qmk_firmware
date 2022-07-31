/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    LFKeyboards
#define PRODUCT         LFK87

#define DIODE_DIRECTION COL2ROW

#ifdef LFK_TKL_REV_A
/* RevB Matrix config */
    #define MATRIX_ROWS 6
    #define MATRIX_COLS 17
    #define MATRIX_ROW_PINS {D2, D3, D4, D5, D6, D7 }
    #define MATRIX_COL_PINS {A0, A1, A2, A3, A4, A5, A6, A7, E6, E7,\
                             F0, F1, F2, F3, C0, C1, C2 }
    #define UNUSED_PINS {B0, B1, B2, B3, B4, B4, B5, B6, B7, C4, C5, C6, C7,\
                         D0, D1, E0, E1, E2, E3, E4, F4, F5, F6, F7}
    #define RGBLED_NUM 25     // Number of LEDs
#else
/* RevC/D Matrix config */
    #define MATRIX_ROWS 7
    #define MATRIX_COLS 16
    #define MATRIX_ROW_PINS {F2, D7, D6, D5, D4, D3, F3}
    #define MATRIX_COL_PINS {A0, A1, A2, A3, A4, A5, A6, A7, C7, C1, C0, E1, E0, C2, C3, C4}
    #define UNUSED_PINS {B0, B1, B2, B3, B4, B4, B5, B6, B7, C5, C6, D2, E3, E4, E5, E6, E7, \
                         F0, F1, F4, F5, F6, F7}
    #define RGBLED_NUM 24     // Number of LEDs
#endif

#define AUDIO_VOICES
#define AUDIO_PIN C6

#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PWM_MAP {2, 4, 8, 16, 40, 55, 70, 128, 200, 255}

#define RGB_DI_PIN F4  // Have to set it to something to get the ws2812 code to compile
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define TAPPING_TERM 200

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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
