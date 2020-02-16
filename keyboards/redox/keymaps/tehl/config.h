/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

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

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 14
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

/* Reverse direction of each LED strip. */
/* The LEDs on my Redox as wired by Falbatech run from the centre towards the
   outside edge on both halves. I want gradients/animations etc to run from
   far-left to far-right across the whole keyboard, so both segments are reversed
   using the LED map.
   Depending on the direction your LEDs are wired (or your lighting preferences),
   you may not need this line. */
#define RGBLIGHT_LED_MAP { 6, 5, 4, 3, 2, 1, 0, 13, 12, 11, 10, 9, 8, 7 }
