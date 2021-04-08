/*
Copyright 2019 mechmerlin

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

#define VENDOR_ID    0x5143 // "QC"
#define PRODUCT_ID   0x4558 // "EX"
#define DEVICE_VER   0x0001
#define MANUFACTURER Quadcube
#define PRODUCT      Exent

#define RGBLED_NUM 18

#define MATRIX_ROWS 7
#define MATRIX_COLS 14

//                         0   1   2   3   4   5   6   7   8   9   A   B   C   D
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5, B6 }
#define MATRIX_COL_PINS { D7, C2, C3, C4, C5, C6, C7, A7, A6, A5, A4, A3, A1, A0 }
#define UNUSED_PINS 

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D1
#define LED_SCROLL_LOCK_PIN D6

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 3

#define RGBLIGHT_ANIMATIONS

/* key combination for magic key command */
/* defined by default; to change, uncomment and set to the combination you want */
// #define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
