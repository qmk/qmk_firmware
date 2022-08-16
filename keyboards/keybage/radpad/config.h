/*
Copyright 2020 Keybage

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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { F5, B5, B6, B2, B3 }
#define MATRIX_COL_PINS { E6, B4, D7, B1 }
#define UNUSED_PINS { B0, B7, C7, D2, D3, D5, F0 }

#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { D4, F6 }
#define ENCODERS_PAD_B { C6, F7 }

#define ENCODER_RESOLUTION 2

#define RGB_DI_PIN F4
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 16
    #define RGBLIGHT_SLEEP
/*== all animations disable ==*/
    #undef RGBLIGHT_ANIMATIONS
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 3

/* OLED Configuration */
#ifdef OLED_ENABLE
    #define OLED_TIMEOUT	    60000
    #define OLED_LOGO_TIMEOUT   3000  // How long (in ms) the logo appears at start up
#endif
