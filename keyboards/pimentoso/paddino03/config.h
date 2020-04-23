/*
Copyright 2020 Michele Ferri <zomgsako@gmail.com>

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
#define VENDOR_ID       0xD00D
#define PRODUCT_ID      0x0030
#define DEVICE_VER      0x0001
#define MANUFACTURER    Pimentoso
#define PRODUCT         Paddino03
#define DESCRIPTION     6-keys 4-layer pad with layer-shifting knob

#define MATRIX_ROWS 1
#define MATRIX_COLS 9
#define MATRIX_ROW_PINS { F4 }
#define MATRIX_COL_PINS { D1, F7, F5, D0, B1, F6, B6, B2, B3 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW // note: no diodes needed

/*
    Rotary encoder
    B2/B3 are used as fake pins for encoder ccw/cw
    B6 is the encoder switch pin
*/
#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { D4 }

/* LED layer indicators */
#define LAYER_INDICATOR_LED_0 D7
#define LAYER_INDICATOR_LED_1 E6
#define LAYER_INDICATOR_LED_2 B4
#define LAYER_INDICATOR_LED_3 B5

/* Bootmagic - hold down rotary encoder pushbutton while plugging in to enter bootloader */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
