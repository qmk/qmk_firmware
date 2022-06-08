/* Copyright 2022 Charue Design

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
#define VENDOR_ID    0x4344 // CD for CharueDesign
#define PRODUCT_ID   0x534E // SN for Supernova
#define DEVICE_VER   0x0001 // Revision 1
#define MANUFACTURER Charue Design
#define PRODUCT      Supernova

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { B3, B2, B1, E6, B7, B0 }
#define MATRIX_COL_PINS { F0, F1, F4, F7, F6, F5, C7, C6, B6, B5, B4, D7, D6, D4, D5, D3 }
#define DIODE_DIRECTION COL2ROW

/* Encoder */
#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D1 }

/* RGB */
#define RGB_DI_PIN D2
#define RGBLED_NUM 1
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_RGB_TEST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
