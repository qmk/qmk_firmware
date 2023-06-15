/*
Copyright 2023 Morgan Venable @_claussen

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

//#include "config_common.h"

/* USB Device descriptor parameter */
/* VID/PID from esp-idf's default tinyusb configuration */
//#define VENDOR_ID       0x303A
//#define PRODUCT_ID      0x4004
//#define DEVICE_VER      0x0002
//#define MANUFACTURER    Svalboard
//#define PRODUCT         Svalboard Alpha RP2040
#define EE_HANDS // must flash left and right separately with option "-bl uf2-split-left" and "-bl uf2-split-right"
#define DIODE_DIRECTION COL2ROW
/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS  10
#define MATRIX_COLS  6
#define MATRIX_ROW_PINS \
    { GP8, GP7, GP6, GP5, GP4 }

#define DEBUG_MATRIX_SCAN_RATE

// wiring of each half
//Layout for svalboard v0 (different from lalboard_v2)
//1 2 3 4 5 6
//S E D N W None
//Both Thumbs (these are same as lalboard_v2)
//OL OU D IL MODE DOUBLE
#define MATRIX_COL_PINS \
    { GP14, GP13, GP12, GP11, GP10, GP9 }


// The column with the "down" keys on both the normal and thumb clusters
// is inverted.  This should be true on all units manufactured after 5/31/2023
#define INVERTED_DOWN_KEYS
#ifdef INVERTED_DOWN_KEYS
    #define MATRIX_COL_PUSHED_STATES { 0, 0, 1, 0, 0, 0 }
#else
    #define MATRIX_COL_PUSHED_STATES { 0, 0, 0, 0, 0, 0 }
#endif
#define MATRIX_COL_PUSHED_STATES_THUMBS { 0, 0, 1, 0, 0, 0 }

#define DOUBLEDOWN_COL 5 // need a pullup on COL6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
/* #define DEBOUNCE 5 */

//#define WS2812_PIO_USE_PIO1

#define SERIAL_DEBUG
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_POINTING_ENABLE
#define SPLIT_ACTIVITY_ENABLE
//#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SERIAL_USART_TX_PIN GP0 
//#define SOFT_SERIAL_PIN GP0
//#define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral
//#undef I2C_DRIVER
//#define I2C_DRIVER I2CD1
//#undef I2C1_SCL_PIN
//#define I2C1_SCL_PIN GP25
//#undef I2C1_SDA_PIN
//#define I2C1_SDA_PIN GP24

/* #define EE_HANDS  */
/* #define MASTER_LEFT */
/* #define MASTER_RIGHT */



/* Top left key on left half */
//#define BOOTMAGIC_LITE_ROW    0
//#define BOOTMAGIC_LITE_COLUMN 0
/* Top right key on right half */
//#define BOOTMAGIC_LITE_ROW_RIGHT    0
//#define BOOTMAGIC_LITE_COLUMN_RIGHT 0
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

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500 // Timeout window in ms in which the double tap can occur.


#define TAPPING_TERM 200 //170 // 200 //120 //00 //90 //200 // how long before a tap becomes a hold



//#define RETRO_TAPPING
//#define IGNORE_MOD_TAP_INTERRUPT
//#undef PERMISSIVE_HOLD                                                                                                  
//#define  PREVENT_STUCK_MODIFIERS


#define MOUSEKEY_DELAY             150 //200
#define MOUSEKEY_INTERVAL          60 //50
#define MOUSEKEY_MAX_SPEED         5  //10
#define MOUSEKEY_TIME_TO_MAX       7 //20
#define MOUSEKEY_WHEEL_MAX_SPEED   5	//8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40
 

#define USB_POLLING_INTERVAL_MS 1




