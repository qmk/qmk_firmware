/*
Copyright 2020 marksard

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

#ifdef RGB_MATRIX_ENABLE
  #define RGB_MATRIX_LED_COUNT 40
  #define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
  // #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
  #define RGB_MATRIX_SLEEP  // turn off effects when suspended
  // #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
  // #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255

//   #undef ENABLE_RGB_MATRIX_ALPHAS_MODS
//   #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//   #undef ENABLE_RGB_MATRIX_BREATHING
//   #undef ENABLE_RGB_MATRIX_BAND_SAT
//   #undef ENABLE_RGB_MATRIX_BAND_VAL
//   #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
//   #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
//   #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
//   #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
//   #undef ENABLE_RGB_MATRIX_CYCLE_ALL
//   #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
//   #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
//   #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
//   #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//   #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//   #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
//   #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
//   #undef ENABLE_RGB_MATRIX_DUAL_BEACON
//   #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
//   #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
//   #undef ENABLE_RGB_MATRIX_RAINDROPS
//   #undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//   #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
//   #undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

//   #define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
//   #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

//   #undef ENABLE_RGB_MATRIX_SPLASH
//   #undef ENABLE_RGB_MATRIX_MULTISPLASH
//   #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
//   #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
#endif
