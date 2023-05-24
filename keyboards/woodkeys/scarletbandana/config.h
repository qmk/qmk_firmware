/*
Copyright 2019 Cole Markham

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
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6969
#define DEVICE_VER      0x0001
#define MANUFACTURER    WoodKeys.click
#define PRODUCT         Scarlet Bandana Version IV mark.2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8    // Number of LEDs
#endif

#define MATRIX_ROW_PINS { D4, D6, D7, B4, B5 }
#define MATRIX_COL_PINS { B2, B3, B7, B1, F5, F4, F6, F7, B0, F0, F1, D0, D1, D2, D5, B6, C7 }

#define QMK_SPEAKER C6

#ifdef AUDIO_ENABLE
#define AUDIO_PIN C6
#define STARTUP_SONG SONG(PREONIC_SOUND)
// Disable music mode to keep the firmware size down
#define NO_MUSIC_MODE
#endif

#define DEBOUNCE 5
