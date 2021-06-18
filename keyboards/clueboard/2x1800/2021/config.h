/*
Copyright 2017 Zach White <skullydazed@clueboard.co>

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

/* audio support */
#define AUDIO_PIN_ALT B7
#define AUDIO_PIN C4
#define AUDIO_CLICKY

/*
 * Encoder Assignments
 */
#define ENCODERS_PAD_A { D0, C5 }
#define ENCODERS_PAD_B { D1, C6 }
#define ENCODER_RESOLUTION 4

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// Configure our MAX7219's
#define MAX7219_LOAD B0
#define MAX7219_CONTROLLERS 4
#define LED_INTENSITY 1  // Max: 15

// Define this to test all LEDs
//#define MAX7219_LED_TEST

// Define this to iterate through LEDs 1 by 1
//#define MAX7219_LED_ITERATE

// Define this to show a simple animation
//#define MAX7219_LED_DANCE

// Define this to show a simple scroll animation
#define MAX7219_LED_SCROLL
