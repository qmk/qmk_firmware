/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 Danny Nguyen <danny@keeb.io>

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

// Use I2C, not Serial 
#define USE_I2C
// Use serial if there's no resistors between the I2C ports
//#define USE_SERIAL

// Select handedness by EEPROM (add :avrdude-split-left or :avrdude-split-right when compiling e.g: make crkbd:default:avrdude-split-left)
#define EE_HANDS

// Alternately, you can set handedness at compilation
//#define MASTER_LEFT
//#define MASTER_RIGHT

/* Key matrix size */
// Rows are doubled-up (to account for the split and stack the halves)
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

// Diode direction
#define DIODE_DIRECTION COL2ROW

// Wiring of left half (my left half only has 6 columns, first 3 pins not used)
#ifdef MATRIX_ROW_PINS
    #undef MATRIX_ROW_PINS
#endif
#ifdef MATRIX_COL_PINS
    #undef MATRIX_COL_PINS
#endif

// Use for left half
#define MATRIX_ROW_PINS { B5, B4, E6, D7, C6 }
#define MATRIX_COL_PINS { F4, F5, D4, F6, F7, B1, B3, B2, B6}

// Use for right half
//#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
//#define MATRIX_COL_PINS { B5, B6, B2, B3, B1, F7, F6, F5, F4 }

// Wiring of right half (todo)
#ifdef MATRIX_ROW_PINS_RIGHT
    #undef MATRIX_ROW_PINS_RIGHT
#endif
#ifdef MATRIX_COL_PINS_RIGHT
    #undef MATRIX_COL_PINS_RIGHT
#endif
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS_RIGHT { B5, B6, B2, B3, B1, F7, F6, F5, F4 }

// Custom layout
#ifdef LAYOUT
    #undef LAYOUT
#endif
#define LAYOUT( \
  LA4, LA5, LA6, LA7, LA8, LA9,      RA1, RA2, RA3, RA4, RA5, RA6, RA7,    RA9  , \
  LB4, LB5, LB6, LB7, LB8, LB9,      RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9, \
  LC4, LC5, LC6, LC7, LC8, LC9,      RC1, RC2, RC3, RC4, RC5, RC6,    RC7  , RC9, \
  LD4, LD5, LD6, LD7, LD8, LD9,      RD1, RD2, RD3, RD4, RD5, RD6, RD7, RD8, RD9, \
  LE4, LE5, LE6, LE7,    LE9  ,         RE1  , RE3, RE4, RE5, RE6, RE7, RE8, RE9 \
  ) \
  { \
    { KC_NO, KC_NO, KC_NO, LA4, LA5, LA6, LA7, LA8, LA9 }, \
    { KC_NO, KC_NO, KC_NO, LB4, LB5, LB6, LB7, LB8, LB9 }, \
    { KC_NO, KC_NO, KC_NO, LC4, LC5, LC6, LC7, LC8, LC9 }, \
    { KC_NO, KC_NO, KC_NO, LD4, LD5, LD6, LD7, LD8, LD9 }, \
    { KC_NO, KC_NO, KC_NO, LE4, LE5, LE6, LE7, KC_NO, LE9 }, \
    { RA1, RA2, RA3, RA4, RA5, RA6, RA7, KC_NO, RA9 }, \
    { RB1, RB2, RB3, RB4, RB5, RB6, RB7, RB8, RB9 }, \
    { RC1, RC2, RC3, RC4, RC5, RC6, RC7, KC_NO, RC9 }, \
    { RD1, RD2, RD3, RD4, RD5, RD6, RD7, RD8, RD9 }, \
    { RE1, KC_NO, RE3, RE4, RE5, RE6, RE7, RE8, RE9 } \
  }

// Pro micro boards have builtin master/slave detection so SPLIT_USB_DETECT isn't needed

// Tapping time for mod-tap
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods (Home row mods)
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat (Home row mods)
#define TAPPING_FORCE_HOLD_PER_KEY






