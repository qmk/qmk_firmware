/*
Copyright 2021 rookiebwoy

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
#define DEVICE_VER      0x0010

/* Column/Row IO definitions */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3
#define MATRIX_ROW_PINS { F4, F5 }
#define MATRIX_COL_PINS { B3, B2, B6 }
#define UNUSED_PINS

/* Dual rotary encoders */
#define ENCODERS_PAD_A { D1, D4 }
#define ENCODERS_PAD_B { D0, C6 }

/* Onboard LEDs */
#define LED_00 F6
#define LED_01 F7

/* Bootmagic - hold down rotary encoder pushbutton while plugging in to enter bootloader */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
