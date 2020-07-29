/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2020 Ben Roe (@ben_roe)

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

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

/* Set 0 if debouncing isn't needed */
#undef DEBOUNCE
#define DEBOUNCE 0

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODERS_PAD_A_RIGHT { F5 }
#define ENCODERS_PAD_B_RIGHT { F4 }

#ifdef RGBLIGHT_ENABLE
  #undef RGB_DI_PIN
  #undef RGBLED_NUM
  #define RGB_DI_PIN D3
  #define RGBLED_SPLIT { 35, 35 }
  #define RGBLED_NUM 70
  #define RGBLIGHT_SPLIT
  #define RGBLIGHT_LIMIT_VAL 120

  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 6 // number of steps to cycle through the hue by
  #define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
  #define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by
  #define RGBLIGHT_SLEEP //  the RGB lighting will be switched off when the host goes to sleep
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
