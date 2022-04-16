/*
Copyright 2020 <contact@vwolf.be>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x5453 // TS - ToastyStoemp
#define PRODUCT_ID   0x0004 // Frog NP
#define DEVICE_VER   0x0001 // Version 1
#define MANUFACTURER    ToastyStoemp
#define PRODUCT         Frog NP

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 4

// Checked with Eagle Schematic
#define MATRIX_ROW_PINS { NO_PIN, F0, B6, D6, B5, D7, B4 }
#define MATRIX_COL_PINS { F5, F6, B7, B3}
#define UNUSED_PINS


//Enoder logic
#ifdef ENCODER_ENABLE

    #define ENCODERS 2

    /* Encoder pins */
    #define ENCODERS_PAD_A { F4, B1 }
    #define ENCODERS_PAD_B { F1, B2 }
    
    /* Encoder Virtual Switches - Column, Row */ 
    #define ENCODERS_CW_KEY  { { 0, 0 },{ 2, 0 } }
    #define ENCODERS_CCW_KEY { { 1, 0 },{ 3, 0 } } 

    /* Encoder resolution */
    #define ENCODER_RESOLUTION 4
    #define TAP_CODE_DELAY 10
    
#endif

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable action features */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
