/*
Copyright 2021 Kyle McCreery
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
#define VENDOR_ID       0x6D77 // mw = "MechWild"
#define PRODUCT_ID      0x1705
#define DEVICE_VER      0x0301
#define MANUFACTURER    MechWild
#define PRODUCT         MurphPad

#define SOFT_SERIAL_PIN D2

//#ifndef SOFT_SERIAL_PIN /* Non-Split Definitions */
///* Key matrix size */
//#define MATRIX_ROWS 6
//#define MATRIX_COLS 5
//
///* Key matrix pins */
//#define MATRIX_ROW_PINS { F5, B2, B3, B1, F7, F6 }
//#define MATRIX_COL_PINS { B5, D7, C6, D4, B6 }
//#define UNUSED_PINS
//
///* Encoder pins in regular mode */
//#define ENCODERS_PAD_A { E6, D2 }
//#define ENCODERS_PAD_B { B4, D3 }
//
///* COL2ROW, ROW2COL */
//#define DIODE_DIRECTION COL2ROW
//
//#else /* Split Definitions */
/* Key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Key matrix pins */
#define MATRIX_ROW_PINS { B5, D7, C6, D4, B6 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, F5 }
#define UNUSED_PINS

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

/* Encoder pins in split mode */
#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { B4 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

//#endif 

/* Encoder resolution */
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10

#define OLED_FONT_H "keyboards/mechwild/murphpad/lib/murphpadfont.c"

#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
#    define RGBLED_SPLIT { 8, 8 }
#    define RGBLED_NUM 16
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
#    define RGBLIGHT_ANIMATIONS
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
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1