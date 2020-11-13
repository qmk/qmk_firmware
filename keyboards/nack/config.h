/*
Copyright 2020 pastapojken <pastapojken@gmail.com>

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

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001
#define MANUFACTURER pastapojken
#define PRODUCT nack keyboard
#define DESCRIPTION nack keyboard

#define MATRIX_ROWS 4
#define MATRIX_COLS 13

#define MATRIX_ROW_PINS { A0, A1, A2, A3 }	
#define MATRIX_COL_PINS { A6, A7, A8, A9, A10, B0, B1, B2, B6, B7, C13, C14, C15 }

#define DIODE_DIRECTION ROW2COL

#ifdef RGB_MATRIX_ENABLE
    #define WS2812_SPI SPID1
    #define WS2812_SPI_MOSI_PAL_MODE 5

    #define RGB_DI_PIN B5
    #define DRIVER_LED_TOTAL 52

    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128 // Max brightness of LEDs 
    #define RGB_MATRIX_STARTUP_VAL 64
    #define RGBLED_NUM 52
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 10
    #define RGBLIGHT_VAL_STEP 10
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
    #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // Valid values: 1 to 2.7
    #define RGBLIGHT_EFFECT_BREATHE_MAX    64   // Max brightness of breathe effect, valid values go from 0 to 255
    /* RGB LED Conversion macro from physical array to electric array */
    #define LED_LAYOUT( \
        L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L10, L11, L12, \
        L13, L14, L15, L16, L17, L18, L19, L20, L21, L22, L23, L24, L25, \
        L26, L27, L28, L29, L30, L31, L32, L33, L34, L35, L36, L37, L38, \
        L39, L40, L41, L42, L43, L44, L45, L46, L47, L48, L49, L50, L51 ) \
      { \
        L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L10, L11, L12, \
        L13, L14, L15, L16, L17, L18, L19, L20, L21, L22, L23, L25, L25, \
        L26, L27, L28, L29, L30, L31, L32, L33, L34, L35, L36, L37, L38, \
        L39, L40, L41, L42, L43, L44, L45, L46, L47, L48, L49, L50, L51 \
      }
      
      #define RGBLIGHT_LED_MAP LED_LAYOUT( \
           0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, \
          25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, \
          26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, \
          51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39 )

#endif

#ifdef AUDIO_ENABLE
    #define AUDIO_PIN A4 // Pin of the left speaker 
    #define AUDIO_PIN_ALT A5 // Pin of the right speaker
    #define AUDIO_DAC_SAMPLE_MAX 4095U
    #define AUDIO_DAC_SAMPLE_WAVEFORM_SQUARE
#endif

#define DEBOUNCE 5

#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif



