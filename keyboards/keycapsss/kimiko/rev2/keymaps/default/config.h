/* Copyright 2019 MechMerlin
 * Copyright 2020 @ben_roe (keycapsss.com)
 * Copyright 2023 @Ex3c4Def
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

/* Select hand configuration */
//------------------------------------------
// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS
//------------------------------------------


// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
//------------------------------------------
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
//------------------------------------------


// 'new' RGB Matrix definitions, used when RGB_MATRIX_ENABLE = yes in rules.mk
//------------------------------------------
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
	// #define RGB_MATRIX_KEYPRESSES
	// #define RGB_MATRIX_KEYRELEASES

	// These modes don’t require any additional defines.
	#define	   ENABLE_RGB_MATRIX_NONE
	#define    ENABLE_RGB_MATRIX_SOLID_COLOR     // Static single hue, no speed support

	#define    ENABLE_RGB_MATRIX_ALPHAS_MODS        // Static dual hue, speed is hue for secondary hue
	// #define    ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN    // Static gradient top to bottom, speed controls how much gradient changes
	// #define    ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes
	// #define    ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
	// #define    ENABLE_RGB_MATRIX_BAND_SAT        // Single hue band fading saturation scrolling left to right
	// #define    ENABLE_RGB_MATRIX_BAND_VAL        // Single hue band fading brightness scrolling left to right
	// #define    ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT   // Single hue 3 blade spinning pinwheel fades saturation
	// #define    ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL   // Single hue 3 blade spinning pinwheel fades brightness
	// #define    ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT     // Single hue spinning spiral fades saturation
	// #define    ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
	// #define    ENABLE_RGB_MATRIX_CYCLE_ALL           // Full keyboard solid hue cycling through full gradient
	// #define    ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
	// #define    ENABLE_RGB_MATRIX_CYCLE_UP_DOWN       // Full gradient scrolling top to bottom
	// #define    ENABLE_RGB_MATRIX_CYCLE_OUT_IN        // Full gradient scrolling out to in
	// #define    ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL   // Full dual gradients scrolling out to in
	// #define    ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradient Chevron shapped scrolling left to right
	// #define    ENABLE_RGB_MATRIX_CYCLE_PINWHEEL      // Full gradient spinning pinwheel around center of keyboard
	// #define    ENABLE_RGB_MATRIX_CYCLE_SPIRAL        // Full gradient spinning spiral around center of keyboard
	// #define    ENABLE_RGB_MATRIX_DUAL_BEACON         // Full gradient spinning around center of keyboard
	#define    ENABLE_RGB_MATRIX_RAINBOW_BEACON      // Full tighter gradient spinning around center of keyboard
	// #define    ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS   // Full dual gradients spinning two halfs of keyboard
	// #define    ENABLE_RGB_MATRIX_RAINDROPS           // Randomly changes a single key's hue
	// #define    ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS // Randomly changes a single key's hue and saturation
	// #define    ENABLE_RGB_MATRIX_HUE_BREATHING       // Hue shifts up a slight ammount at the same time, then shifts back
	// #define    ENABLE_RGB_MATRIX_HUE_PENDULUM        // Hue shifts up a slight ammount in a wave to the right, then back to the left
	// #define    ENABLE_RGB_MATRIX_HUE_WAVE            // Hue shifts up a slight ammount and then back down in a wave to the right
	// #define    ENABLE_RGB_MATRIX_PIXEL_FRACTAL       // Single hue fractal filled keys pulsing horizontally out to edges
	// #define    ENABLE_RGB_MATRIX_PIXEL_FLOW          // Pulsing RGB flow along LED wiring with random hues
	// #define    ENABLE_RGB_MATRIX_PIXEL_RAIN          // Randomly light keys with random hues

	// These modes also require the RGB_MATRIX_FRAMEBUFFER_EFFECTS define to be available.
	#define    ENABLE_RGB_MATRIX_TYPING_HEATMAP      // How hot is your WPM!
	// #define    ENABLE_RGB_MATRIX_DIGITAL_RAIN        // That famous computer simulation

	// These modes also require the RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES define to be available.
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE      // Static single hue, pulses keys hit to shifted hue then fades to current hue
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
	// #define    ENABLE_RGB_MATRIX_SPLASH              // Full gradient & value pulse away from a single key hit then fades value out
	// #define    ENABLE_RGB_MATRIX_MULTISPLASH         // Full gradient & value pulse away from multiple key hits then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_SPLASH        // Hue & value pulse away from a single key hit then fades value out
	// #define    ENABLE_RGB_MATRIX_SOLID_MULTISPLASH   // Hue & value pulse away from multiple key hits then fades value out

	#define RGB_MATRIX_VAL_STEP 4
	#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
	#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
	#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
	#define RGB_MATRIX_DEFAULT_VAL 60 //RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
	#define RGB_MATRIX_DEFAULT_SPD 60 // Sets the default animation speed, if none has been set
//------------------------------------------


// 'old' RGB Lightning definitions, used when RGBLIGHT_ENABLE = yes in rules.mk
//------------------------------------------
#   define RGBLIGHT_HUE_STEP 8
#   define RGBLIGHT_SAT_STEP 8
#   define RGBLIGHT_VAL_STEP 8
#   define RGBLIGHT_SLEEP       /* the RGB lighting will be switched off when the host goes to sleep */
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
//------------------------------------------


// pointing device definitions
//------------------------------------------
#if defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
#    define POINTING_DEVICE_ROTATION_180 // may be used for trackball in 2nd position
#endif
//------------------------------------------


