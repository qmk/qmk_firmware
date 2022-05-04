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

#define PRODUCT_ID                  0x3536
#define DEVICE_VER                  0x0001

// wiring of each half
#define MATRIX_ROW_PINS { B7, D5, C7, F1, F0 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define DIODE_DIRECTION COL2ROW
/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/*
// WS2812 RGB LED strip input and number of LEDs
#define RGB_DI_PIN D3
#define DRIVER_LED_TOTAL 57
// Left, Right
#define RGB_MATRIX_SPLIT { 27, 30} 
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_SOLID_COLOR
#define RGBLIGHT_DEFAULT_COLOR HSV_BLUE
*/

// Data sync options
#define SPLIT_TRANSPORT_MIRROR
//#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_CONFIG_SYNC
// Split settings
#define USE_I2C
#define MASTER_RIGHT
#define SPLIT_USB_DETECT

// audio
//#define AUDIO_PIN F4
// As per docs, must be one of: C4, C5, C6, B5, B6, B7

// Trackball - PMW3360 Settings
#define PMW3360_CS_PIN F7
// don't think we need this...did not fix the "one half only = no worky" issue; did not break trackball functionality tho - leave out
// #define SPLIT_POINTING_ENABLE
//#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_RIGHT
#define PMW3360_CPI 400
#define ROTATIONAL_TRANSFORM_ANGLE  -75
#define POINTING_DEVICE_INVERT_X
//#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_TASK_THROTTLE_MS 1
#define PMW3389_LIFTOFF_DISTANCE 0x04

// #define DYNAMIC_KEYMAP_LAYER_COUNT  16
// #define LAYER_STATE_16BIT
