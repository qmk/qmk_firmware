/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Ben Roesner (keycapsss.com)

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

/* Select hand configuration. Either select master_left or -right before compiling/flashing or
use define EE_HANDS at flashing time*/
// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define TAPPING_TERM 150  // mod tap hold time (shift) in ms, default 200

#define ENCODER_DIRECTION_FLIP    // Change analog encoder rotation direction
#define ENCODER_RESOLUTION 1

// Optimizations
#define NO_MUSIC_MODE
//#define SPLIT_LAYER_STATE_ENABLE  // layer activation needs to be send to slave side for RGB change
//#define RGBLIGHT_ENABLE is already defined

#ifdef RGBLIGHT_ENABLE
// RGBLIGHT_SPLIT      bereits hier definiert: ./keyboards/lily58/light/config.h
// RGBLIGHT_LIMIT_VAL LED max. bright level: ./keyboards/lily58/light/config.h
//#  define RGBLIGHT_LAYERS_RETAIN_VAL // Lightning layers should retain the set main brightness 
  
#  define RGBLIGHT_SLEEP      // the RGB lighting will be switched off when the host goes to sleep
// #  define RGBLIGHT_ANIMATIONS  // deprecated!
#  define RGBLIGHT_HUE_STEP 6 // number of steps to cycle through the hue by
#  define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
#  define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by

// #  define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL

#  define RGBLIGHT_EFFECT_ALTERNATING  // manuell ansteuern
#  define RGBLIGHT_EFFECT_BREATHING
#  define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#  define RGBLIGHT_EFFECT_RGB_TEST
#  define RGBLIGHT_EFFECT_SNAKE
#  define RGBLIGHT_EFFECT_STATIC_GRADIENT
#endif


// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
//#define SPLIT_USB_DETECT
//#define NO_USB_STARTUP_CHECK


