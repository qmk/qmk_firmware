/*
Copyright 2021 ihsankeskin.org

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
#define VENDOR_ID       0xCA04
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER KeskinTech
#define PRODUCT KeskinTech Macro Keyboard

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 15
#define MATRIX_COL_PINS { B11, B10, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0, C15, C14, C13}
#define MATRIX_ROW_PINS { B5, B6, B4, B7, B3, B8, A15}
#define DIODE_DIRECTION COL2ROW


/* Dıp Swich Pin */
#define DIP_SWITCH_PINS {B15, A9, A10}

/*
#define BACKLIGHT_PIN A8
#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_LEVELS 6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 6
*/

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Hardware LED pins*/
#define LED_CAPS_LOCK_PIN B12
#define LED_NUM_LOCK_PIN B13
#define LED_COMPOSE_PIN B14
#define LED_PIN_ON_STATE 1

/* Hardware AUDİO pins*/


/* Hardware AUDİO pins*/
 #define AUDIO_PIN A8
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL 1
#define AUDIO_PWM_PAL_MODE 42
#define AUDIO_STATE_TIMER GPTD4
  #define AUDIO_CLICKY
  #define AUDIO_CLICKY_ON

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(ROCK_A_BYE_BABY)
  #define GOODBYE_SONG SONG(GOODBYE_SOUND)
  #define AG_NORM_SONG SONG(AG_NORM_SOUND)
  #define MUSIC_ON_SONG SONG(MUSIC_ON_SOUND)
  #define AUDIO_ON_SOUNG SONG(AUDIO_ON_SOUND)
  #define AUDIO_OFF_SOUNG SONG(AUDIO_OFF_SOUND)
  #define MUSIC_OFF_SOUNG SONG(MUSIC_OFF_SOUND)
  #define CAPS_LOCK_ON_SOUNG SONG(CAPS_LOCK_ON_SOUND)
  #define CAPS_LOCK_OFF_SOUNG SONG(CAPS_LOCK_OFF_SOUND)
  #define SCROLL_LOCK_ON_SOUNG  SONG(SCROLL_LOCK_ON_SOUND)
  #define SCROLL_LOCK_OFF_SOUNG SONG(SCROLL_LOCK_OFF_SOUND)
  #define NUM_LOCK_ON_SOUNG SONG(NUM_LOCK_ON_SOUND)
  #define NUM_LOCK_OFF_SOUNG SONG(NUM_LOCK_OFF_SOUND)
  #define TERMINAL_SOUNG SONG(TERMINAL_SOUND)
#endif

/*#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN B9
#define RGBLED_NUM 9
*/
#define WS2812_SPI SPID2
#define WS2812_SPI_MOSI_PAL_MODE 5


#define TERMINAL_HELP
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 100

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
#define FORCE_NKRO


/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
