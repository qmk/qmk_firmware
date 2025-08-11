/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

#define SPLIT_RGB_MATRIX_ENABLE
#define RGB_MATRIX_SPLIT_SYNC
#define SPLIT_TRANSPORT_MIRROR

#define RGB_MATRIX_DEFAULT_HUE 80    // Hue for blue (0=red, 85=green, 170=blue)
#define RGB_MATRIX_DEFAULT_SAT 100   // Full saturation (255 = full color)
#define RGB_MATRIX_DEFAULT_VAL 50  // Full brightness

#define RGB_DI_PIN D3

#define DYNAMIC_KEYMAP_LAYER_COUNT = 5

#define LED_PIN_ON_STATE 0
