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
//#define MAX7219_LOAD B0
//#define MAX7219_CONTROLLERS 4
//#define MAX7219_LED_INTENSITY 1  // Max: 15

// Define this to disable the startup test
//#define MAX7219_NO_STARTUP_TEST

/* This controls the speed of the sign, lower is faster. This is the minimal
 * time between animation frames, in ms. Actual time between frames will
 * always be slightly longer due to other keyboard tasks.
 */
//#define MAX7219_SCROLL_TIME 100

/* This setting controls how big the scrollable area for your message sign
 * is. If you set it to 0 your display will not work. If you set it to 1
 * you will have no buffer area, and you will only be able to display a
 * total of 6 characters. Every number after that increases the buffer area
 * by 32 columns.
 *
 * You can calculate how big to make this for the number of characters you
 * want to display:
 *
 *     <number of characters in message> * 6 / 32 + 1
 *
 * You do not need to tune this unless you are trying to save ram.
 */
//#define MAX7219_BUFFER_MULTIPLIER 24

// You can only define one of these at a time:

// Define this to test all LEDs. Keyboard functions will not work.
//#define MAX7219_LED_TEST

// Define this to iterate through LEDs 1 by 1. Keyboard functions will not work.
//#define MAX7219_LED_ITERATE

// Define this to show a simple animation. Keyboard functions will not work.
//#define MAX7219_LED_DANCE

// Define this to show all the characters available
//#define MAX7219_LED_FONTTEST

// Define this to show Clueboard on the sign
//#define MAX7219_LED_CLUEBOARD

// Define this to show the Konami code on the sign
//#define MAX7219_LED_KONAMI

// Define this to show QMK on the sign
//#define MAX7219_LED_QMK_POWERED

// Define this to treat the message board like an etch-a-sketch
//#define DRAWING_TOY_MODE

// Define this if you don't want any of the above
//#define MAX7219_LED_CUSTOM
