/*
Copyright 2022 GEIST <@geigeigeist>

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
#define VENDOR_ID       0x3A3C
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    GEIST
#define PRODUCT         KLOR


/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6


// wiring of each half
#define MATRIX_ROW_PINS { C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }
#define DIODE_DIRECTION COL2ROW

#define UNUSED_PINS


/* audio support */
#define AUDIO_VOICES
#define AUDIO_PIN B5

//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#define DEBOUNCE 5


/* encoder support */
#define ENCODERS_PAD_A       { F5 }
#define ENCODERS_PAD_B       { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTION 2


/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2
//#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_USB_DETECT
#define SERIAL_USE_MULTI_TRANSACTION


/* rgb led support */
#define RGB_DI_PIN D3
#define RGBLED_NUM 42
#define RGBLED_SPLIT { 21, 21 }
#define RGBLIGHT_ANIMATIONS


#ifdef HAPTIC_ENABLE
#    define FB_ERM_LRA 1
#    define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 
#    define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3 
#    define RATED_VOLTAGE 2
#    define V_PEAK 2.8
#    define V_RMS 2.0 
#    define F_LRA 150 // resonance freq 
#    define DRV_GREETING       alert_750ms
#endif


#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#    define OLED_FONT_H  "./lib/glcdfont.c"
#endif


#ifdef AUDIO_ENABLE
#    define NO_MUSIC_MODE
#    define STARTUP_SONG SONG(PREONIC_SOUND)
#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND) }
#endif 


#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define DRIVER_LED_TOTAL 42 // Number of LEDs
#    define RGB_MATRIX_SPLIT { 21, 21 }
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#    define RGB_MATRIX_STARTUP_HUE 35
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#endif 

