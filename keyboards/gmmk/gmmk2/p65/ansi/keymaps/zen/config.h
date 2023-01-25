/* Copyright 2023 zen <github@desultory>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects

// Undefine rgb modes enabled for the keyboard but not used
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW

#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

// Set default RGB speed
#define RGB_MATRIX_DEFAULT_SPD 64

// Ensure matrix framebuffer and keypresses are set
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP // effect 4
    #if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
	#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE // effect 5
	#define ENABLE_RGB_MATRIX_SOLID_REACTIVE // effect 6
	#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE // effect 7
	#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // effect 8
	#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // effect 9
    #endif
#endif

// define other enabled rgb modes
#define ENABLE_RGB_MATRIX_PIXEL_RAIN // effect 3
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON // effect 2

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_BEACON

// force enable n key rollover
#define FORCE_NKRO

// Enable leader, set timeout to 500ms
#define LEADER_TIMEOUT 500

// Enable leader per key timing which restarts the timeout each time a key is pressed
#define LEADER_PER_KEY_TIMING

// Disable timeout, so leader can be pressed and then action can be taken
#define LEADER_NO_TIMEOUT

// Make control+shift+escape work
#define GRAVE_ESC_CTRL_OVERRIDE
