/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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


// wiring of each half
// Ascii art of pro micro. Pin names PD3, PD2, etc.
//Usage| Name | Label      Label| Name | Usage
//                   PORT          
//     | PD3    TX0        RAW       |
//     | PD2    RX1        GND       |SerGnd
//     |        GND        RESET     |
//     |        GND        VCC       |SerVCc
//     | PD1    2          A3    PF4 | Col7
//Ser  | PD0    3          A2    PF5 | Col6
//Row4 | PD4    4          A1    PF6 | Col5
//AUDIO| PC6    5          A0    PF7 | Col4
//Row3 | PD7    6          15    PB1 | Col3
//Row2 | PE6    7          14    PB3 | Col2
//Row1 | PB4    8          13    PB2 | Col1
//Row0 | PB5    9          10    PB6 | Col0

// Note reservation of C6 for audio
#define MATRIX_ROW_PINS { B5, B4, E6, D7, D4 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#define IGNORE_MOD_TAP_INTERRUPT
