/*
Copyright 2020 latincompass

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "config_common.h"
#define VENDOR_ID       0x6C63 // "lc" = latincompass
#define PRODUCT_ID      0x6C70 // "lp" = latinpad
#define DEVICE_VER      0x0001
#define MANUFACTURER    latincompass
#define PRODUCT         latinpad
#define DESCRIPTION     dual rotary encoder macro pad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1 }
#define MATRIX_COL_PINS { D4, C6, D7, E6 }
#define UNUSED_PINS

#define DIODE_DIRECTION ROW2COL

#define SSD1306OLED
#define RGB_DI_PIN D3

#define RGBLED_NUM 18
#define DRIVER_LED_TOTAL RGBLED_NUM

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE


#define OLED_FONT_H "./lib/glcdfont.c"

#define ENCODERS_PAD_A { B4, B5 }
#define ENCODERS_PAD_B { B2, B6 }

#define ENCODER_RESOLUTION 4
