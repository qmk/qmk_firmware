/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

//#define SOLENOID_ENABLE
//#define SOLENOID_PIN C6

/* Use I2C or Serial, not both */

#define USE_SERIAL
//#define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT

// #define AUDIO_CLICKY
// #define AUDIO_CLICKY_ON
// #define C6_AUDIO
// #define AUDIO_CLICKY_FREQ_RANDOMNESS 0.1f
// #define AUDIO_CLICKY_FREQ_MAX 100.0f

// #define MASTER_RIGHT
// #define EE_HANDS

// #undef RGBLED_NUM
// #define RGBLIGHT_ANIMATIONS
// #define RGBLED_NUM 12
// #define RGBLIGHT_HUE_STEP 8
// #define RGBLIGHT_SAT_STEP 8
// #define RGBLIGHT_VAL_STEP 8

#endif
