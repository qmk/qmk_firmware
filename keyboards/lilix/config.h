/*
Copyright 2021 Elizabeth Bodaneze

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
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x3A33 // :3
#define DEVICE_VER   0x0001
#define MANUFACTURER Elizabeth Bodaneze
#define PRODUCT      Lilix Alpha
#define DESCRIPTION  A Helix spin off
#define USB_MAX_POWER_CONSUMPTION 500



/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
/* Soft Serial defines */
#define SOFT_SERIAL_PIN D2
#define SERIAL_USE_MULTI_TRANSACTION
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_USER RPC_ID_SYNC_STATE_USER

//#define SELECT_SOFT_SERIAL_SPEED 3

/* Select hand configuration */
#define SPLIT_USB_DETECT
//#define MASTER_RIGHT
//#define MASTER_LEFT
//#define EE_HANDS
//#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_MODS_ENABLE



/* key matrix size */
#define MATRIX_ROWS 10
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
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5



//RGB LED support
/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_SPLIT
#define RGBLED_NUM 32
#define RGBLIGHT_LIMIT_VAL 120 /* The maximum brightness level */
                               // - LEDs tend to burn out past 130, so keep it lower than that
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 18
#define RGBLIGHT_VAL_STEP 18

#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== choose RGB light animations ==*/
//#define RGBLIGHT_EFFECT_BREATHING
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#define RGBLIGHT_EFFECT_SNAKE
//#define RGBLIGHT_EFFECT_KNIGHT
//#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#define RGBLIGHT_EFFECT_RGB_TEST
//#define RGBLIGHT_EFFECT_ALTERNATING
//#define RGBLIGHT_EFFECT_TWINKLE

/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#define RGBLIGHT_EFFECT_BREATHE_MAX    120   // 0 to 255
/*== customize swirl range ==*/
//#define RGBLIGHT_RAINBOW_SWIRL_RANGE 200

/*== enable RGB layers ==*/
#define RGBLIGHT_LAYERS
//#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF



//OLED
//#define OLED_SCROLL_TIMEOUT 1000
#define OLED_TIMEOUT 20000
#define OLED_UPDATE_INTERVAL 1
#define OLED_FONT_H "glcdfont.h"
//#define OLED_FONT_END 224



/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE



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



/* Key tapping configuration */
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200



/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0



/* Oneshot keys configuration */
//#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
//#define ONESHOT_TIMEOUT 1000  /* Time (in ms) before the one shot key is released */



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
#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
