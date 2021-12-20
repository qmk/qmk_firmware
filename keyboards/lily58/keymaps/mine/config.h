/*
This is the c configuration file for the keymap

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

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define MASTER_RIGHT
#define USE_SERIAL_PD2
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

// Underglow
#undef RGBLED_NUM
#ifdef RGBLIGHT_ENABLE
  #define RGBLED_NUM 16
  #define RGBLED_SPLIT {8,8}
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LAYERS
#endif 

// Encoder
#ifdef ENCODER_ENABLE 
  #define ENCODERS_PAD_A { F5 }
  #define ENCODERS_PAD_B { F4 }
  #define ENCODER_RESOLUTION 2
  
  // Enable if encoder is on the left side
  // #define ENCODER_DIRECTION_FLIP
#endif