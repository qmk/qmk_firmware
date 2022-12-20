/*
Copyright 2021 Takeshi Nishio

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
// Same number for Round-Robin matrix.
#define MATRIX_ROWS 10
#define MATRIX_COLS 10

// Same pins for Round-Robin matrix.
#define MATRIX_ROW_PINS { B3, B2, E6, D6, D4, B0, B1, B7, B4, D7 }
#define MATRIX_COL_PINS { B3, B2, E6, D6, D4, B0, B1, B7, B4, D7 }

#define DIODE_DIRECTION COL2ROW

/* Rotary Encoder */
#define ENCODERS_PAD_A { F5, D2 }
#define ENCODERS_PAD_B { F4, D3 }
#define ENCODER_RESOLUTION 4  //the default & suggested is 4

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN C6
  #define AUDIO_CLICKY
  #define MUSIC_MAP
#endif

/* RGBLIGHT */
#define RGB_DI_PIN F1
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 4 // Left(2) + Right(2)
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  /*== Lighting Layers ==*/
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite trigger key. Left-Top of the layout. */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 9

/* External EEPROM */
// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64
// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191
// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 6 // default:4
