/*
Copyright 2021 bryan065

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
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER bryan065
#define PRODUCT      GHero20

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

/* Set power level for Bluefruit
*
* Valid parameters: -40, -20, -16, -12, -8, -4, 0, 4
* (https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/ble-generic#at-plus-blepowerlevel)
*
* Used with my customized version of adafruit_ble
*/
#define POWER_LEVEL 4

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
#define MATRIX_ROW_PINS { B6, B7, D6, C7 }
#define MATRIX_COL_PINS { F6, F5, F4, F1, F0 }

#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define OUTPUT_AUTO_ENABLE

/* Adafruit BLE SPI Friend */
#define AdafruitBleResetPin D4
#define AdafruitBleCSPin B4
#define AdafruitBleIRQPin E6

#define QMK_KEYS_PER_SCAN 8

/*
* MPU9250 Settings
*
* MPU_ANGLE_SENS: Angle at which the star power starts to activate.
* Default: 60       Max: 100    Min: 50
* MPU_SPEED_SENS: Speed at which the star power activates, used to prevent unintentional star power usage.
* Default: 700      Max: 2000   Min: 200
*
* STAR_LEFT_HAND: Uncomment for left handed users to activate star power.
*/
#define MPU_ANGLE_SENS 60
#define MPU_SPEED_SENS 700
//#define STAR_LEFT_HAND

#define RGB_DI_PIN C6
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 7
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 255      /* The maximum brightness level */
    #define RGBLIGHT_DEFAULT_VAL 255
    #define RGBLIGHT_SLEEP              /* If defined, the RGB lighting will be switched off when the host goes to sleep */
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable action features */
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
