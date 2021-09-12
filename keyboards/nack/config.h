/*
Copyright 2020 farfalleflickan <farfalleflickan@gmail.com>

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

#define VENDOR_ID 0xDA12
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001
#define MANUFACTURER farfalleflickan
#define PRODUCT nack keyboard

#define MATRIX_ROWS 4
#define MATRIX_COLS 13

#define MATRIX_ROW_PINS { A0, A1, A2, A3 }
#define MATRIX_COL_PINS { A6, A7, A8, A9, A10, B0, B1, B2, B6, B7, C13, C14, C15 }

#define DIODE_DIRECTION ROW2COL
#define DEBOUNCE 5
#define TAPPING_TOGGLE 2

#ifdef RGB_MATRIX_ENABLE
    #define WS2812_SPI SPID1
    #define WS2812_SPI_MOSI_PAL_MODE 5
    #define RGB_DI_PIN B5
    #define RGBLED_NUM 52
    #define DRIVER_LED_TOTAL RGBLED_NUM
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128 // Max brightness of LEDs
    #define RGB_MATRIX_STARTUP_VAL 64
    #define RGB_MATRIX_HUE_STEP 10
    #define RGB_MATRIX_SAT_STEP 10
    #define RGB_MATRIX_VAL_STEP 10
#endif

#ifdef AUDIO_ENABLE
    #define AUDIO_PIN A5
    #define AUDIO_PIN_ALT A4
    #define STARTUP_SONG SONG(NO_SOUND)
    #define AUDIO_DAC_SAMPLE_MAX 4095U
#endif
