/*
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

#include "config_common.h"

#define PRODUCT Tractyl Manuform(5x6) Elite C
//#define PRODUCT_ID                  0x3536
// PRODUCT_ID is really only used by the OS, and is arbitrary.
#define PRODUCT_ID                  0x1234
#define DEVICE_VER                  0x0001
/* USB Device descriptor parameter */
#define VENDOR_ID               0x44DD

// wiring of each half
#define MATRIX_ROW_PINS { B7, D5, C7, F1, F0 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define DIODE_DIRECTION COL2ROW
/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1

// keyboard config
// this is how long 'hold for effect' takes; 300 feels way too long, 200 causes too many accidental triggers
#define TAPPING_TERM 250
#define DEBOUNCE 5 // trying this down from 45, apparently can contribute to input lag

// Split settings
#if defined(SPLIT_KEYBOARD)
    #define SPLIT_TRANSPORT_MIRROR      // docs say use this if you are using RGB_MATRIX_SPLIT { X, Y }
    #define SPLIT_LAYER_STATE_ENABLE    // docs say use this if you are using split and rgb lighting per layer
    #define SPLIT_MODS_ENABLE           // not sure why
    #define EE_HANDS                    // cuz we are using hand-targeted flashing, which sets eeprom handednesss
    #define SPLIT_USB_DETECT            // the usb cable sets master
    #define USE_SERIAL                  // vs. I2C, which I was advised against doing
    #define SOFT_SERIAL_PIN D2          // where is your TRRS data pin hooked up on the MCU
    #    if defined(__AVR__) && !defined(SELECT_SOFT_SERIAL_SPEED)
    #        define SELECT_SOFT_SERIAL_SPEED 1
    #    endif
    #    ifdef CUSTOM_SPLIT_TRANSPORT_SYNC // this seems super fancy and I haven't looked at why there's so much here...
    #        define SPLIT_TRANSACTION_IDS_USER RPC_ID_USER_STATE_SYNC, RPC_ID_USER_KEYMAP_SYNC, RPC_ID_USER_CONFIG_SYNC, RPC_ID_USER_WATCHDOG_SYNC, RPC_ID_USER_KEYLOG_STR
    #    endif
#endif

// audio - takes up a lot of memory
//#define AUDIO_PIN F4
// As per docs, must be one of the PWM pins: C4, C5, C6, B5, B6, B7

#ifdef POINTING_DEVICE_ENABLE    
    #define PMW3360_CS_PIN F7 // Trackball - PMW3360 Settings
    #define PMW3360_LIFTOFF_DISTANCE 0x04 // LIFTOFF_DISTANCE specifies how far from the sensor the trackball is
    #define PMW3360_CPI 1200 // your DPI setting, how fast the ball tracks
    #define POINTING_DEVICE_RIGHT // Which keyboard half contains the trackball
    #define ROTATIONAL_TRANSFORM_ANGLE -85 // Software adjustment for how not-squarely you packaged the sensor
    #define POINTING_DEVICE_INVERT_X // Inverted movement for X (not sure why this is set tbh...maybe due to the kb half it's installed on?)
    #define POINTING_DEVICE_TASK_THROTTLE_MS 1 // Not sure what this does...
    #define CHARYBDIS_MINIMUM_DEFAULT_DPI PMW3360_CPI // the drag-scroll code uses this to maintain DPI/CPI between modes
//  #define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 200

#endif

// WS2812 RGB LED strip input and number of LEDs
#ifdef RGB_MATRIX_ENABLE
    #define RGB_DI_PIN D3
    #define RGBLED_NUM 57  // Total number of LEDs
    #define DRIVER_LED_TOTAL RGBLED_NUM // some other code uses driver-led-total
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 90 // setting this too high will cause the trackball to reset every min or so, and at highest just brownout entirely
    #define RGB_MATRIX_SPLIT { 27, 30} // led count; left, right
#endif

/* Disable unused and unneeded features to reduce on firmware size */
// this made no difference
// #ifdef LOCKING_SUPPORT_ENABLE
// #    undef LOCKING_SUPPORT_ENABLE
// #endif
// #ifdef LOCKING_RESYNC_ENABLE
// #    undef LOCKING_RESYNC_ENABLE
// #endif
