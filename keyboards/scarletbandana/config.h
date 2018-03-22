/*
Copyright 2017 Cole Markham

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6969
#define DEVICE_VER      0x0001
#define MANUFACTURER    WoodKeys.click
#define PRODUCT         Scarlet Bandana Version IV mark.2
#define DESCRIPTION     What keyboard is that?

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION CUSTOM_MATRIX

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLIGHT_TIMER
#define RGBLED_NUM 8    // Number of LEDs
#endif

#define MATRIX_ROW_PINS { D4, D6, D7, B4, B5 }
// Column pins to demux in LSB order
//#define MATRIX_COL_PINS { F1, F4, F5, F6 }
#define MATRIX_COL_PINS { F6, F5, F4, F1 }
#define MATRIX_XCOL_PINS { F0 }
#define MATRIX_EN_PIN F7
#define UNUSED_PINS

#define QMK_SPEAKER C6

#define AUDIO_VOICES
#define C6_AUDIO

#define DEBOUNCING_DELAY 5

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#endif
