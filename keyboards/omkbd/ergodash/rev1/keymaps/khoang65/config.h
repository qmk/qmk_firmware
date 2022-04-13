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

/* Use I2C or Serial, not both */
#define USE_SERIAL

/* Select hand configuration */
#define MASTER_LEFT

/* Select Leader Key Timeout (ms) */
#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 250
//#define LEADER_PER_KEY_TIMING 75 // fickle

#ifdef RGB_MATRIX_ENABLE

#	undef RGB_MATRIX_STARTUP_MODE
#	undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#	undef RGB_MATRIX_LED_FLUSH_LIMIT
#	define RGB_MATRIX_STARTUP_MODE RGB_MODE_PLAIN
#	define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#	define RGB_MATRIX_LED_FLUSH_LIMIT 16 // default: 26 

/* Active RBG Modes */

/* Disabling to optimize firmware size */
#	define DISABLE_RGB_MATRIX_TYPING_HEATMAP   		    // How hot is your WPM!
#	define DISABLE_RGB_MATRIX_SPLASH           	    	// Full gradient & value pulse away from a single key hit then fades value out 
#	define DISABLE_RGB_MATRIX_SOLID_SPLASH         		// Hue & value pulse away from a single key hit then fades value out 
#	define DISABLE_RGB_MATRIX_ALPHAS_MODS         		// Static dual hue, speed is hue for secondary hue 
#	define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT 		// Static gradient left to right, speed controls how much gradient changes
#	define DISABLE_RGB_MATRIX_BREATHING           		// Single hue brightness cycling animation 
#	define DISABLE_RGB_MATRIX_BAND_VAL            		// Single hue band fading brightness scrolling left to right 
#	define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL   		// Single hue 3 blade spinning pinwheel fades brightness 
#	define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL     		// Single hue spinning spiral fades brightness
#	define DISABLE_RGB_MATRIX_CYCLE_ALL           		// Full keyboard solid hue cycling through full gradient
#	define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    		// Full gradient scrolling left to right
#	define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN       		// Full gradient scrolling top to bottom
#	define DISABLE_RGB_MATRIX_CYCLE_OUT_IN        		// Full gradient scrolling out to in
#	define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL   		// Full dual gradients scrolling out to in
#	define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradent Chevron shapped scrolling left to right
#	define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL      		// Full gradient spinning pinwheel around center of keyboard
#	define DISABLE_RGB_MATRIX_CYCLE_SPIRAL        		// Full gradient spinning spiral around center of keyboard
#	define DISABLE_RGB_MATRIX_DUAL_BEACON         		// Full gradient spinning around center of keyboard
#	define DISABLE_RGB_MATRIX_RAINBOW_BEACON      		// Full tighter gradient spinning around center of keyboard
#	define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS   		// Full dual gradients spinning two halfs of keyboard
#	define DISABLE_RGB_MATRIX_RAINDROPS           		// Randomly changes a single key's hue
#	define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS 		// Randomly changes a single key's hue and saturation
#	define DISABLE_RGB_MATRIX_SOLID_REACTIVE      		// Static single hue, pulses keys hit to shifted hue then fades to current hue
#endif /* RGB_MATRIX_ENABLE */


/* Firmware Size Optimimzation */
#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT