/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Ben Roesner (keycapsss.com)
Copyright 2022 Vii33 (https://github.com/vii33/mecha-keyboard-lily58l)

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

/* Hand configuration needs to be set at flashing time: 
qmk flash -kb lily58/light -km lily58l_vii33 -bl dfu-split-left
*/
#define EE_HANDS

// Home row modifiers   https://precondition.github.io/home-row-mods
#define TAPPING_TERM 200          // mod tap hold time (shift) in ms, default 200
#define IGNORE_MOD_TAP_INTERRUPT  // important for good home row mods experience
#define TAPPING_FORCE_HOLD        // activate the hold function, when holding a dual-role key
                                  // after having tapped it.No more accidental repeats of mod-tap letters when typing quickly!
// The downside is that it removes the possibility of auto-repeating the letter/tapping function of the mod-tap.
// BUT The good news is that there exists a per-key variant of this configuration option: TAPPING_FORCE_HOLD_PER_KEY
// ->> Just enable it for your home row modifiers


#define ENCODER_DIRECTION_FLIP    // Change analog encoder rotation direction -> cw: down / volume louder
#define ENCODER_RESOLUTION 1

#define NO_MUSIC_MODE


/* Defined in other files. See ./keyboards/lily58/light/config.h:
  RGBLIGHT_ENABLE
  RGBLIGHT_SPLIT
  RGBLIGHT_LIMIT_VAL
*/

#ifdef RGBLIGHT_ENABLE
#  define RGBLIGHT_SLEEP      // the RGB lighting will be switched off when the host goes to sleep
#  define RGBLIGHT_HUE_STEP 1 // number of steps to cycle through the hue by
#  define RGBLIGHT_SAT_STEP 2 // number of steps to increment the saturation by
#  define RGBLIGHT_VAL_STEP 2 // number of steps to increment the brightness by

#  define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_GRADIENT

#  define RGBLIGHT_EFFECT_ALTERNATING  
#  define RGBLIGHT_EFFECT_BREATHING
#  define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#  define RGBLIGHT_EFFECT_RGB_TEST
#  define RGBLIGHT_EFFECT_SNAKE
#  define RGBLIGHT_EFFECT_STATIC_GRADIENT
#  undef RGBLIGHT_EFFECT_TWINKLE
#  undef RGBLIGHT_EFFECT_KNIGHT

// Custom Lightning Layers
#  define RGBLIGHT_LAYERS
#  define RGBLIGHT_MAX_LAYERS 2  // Default is 8. Performance impact -> reduced to 2
#endif


// OLED
#define OLED_TIMEOUT 120000
#define OLED_FADE_OUT
#define OLED_UPDATE_INTERVAL 150  // set oled update interval in ms (default: 0). improves matrix scan rate
#define OLED_BRIGHTNESS 120

// Sync WPM to slave side
#define SPLIT_WPM_ENABLE    
// #define SPLIT_OLED_ENABLE

#define SPLIT_USB_DETECT

// ACTIVATE for Elite C rev3 controller on the slave side
//#define NO_USB_STARTUP_CHECK

