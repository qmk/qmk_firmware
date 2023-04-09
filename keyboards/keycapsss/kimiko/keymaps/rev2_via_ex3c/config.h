/* Copyright 2019 MechMerlin
 * Copyright 2023 @ben_roe (keycapsss.com)
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
// #define MANUFACTURER    keycapsss.com
// #define PRODUCT         Kimiko Rev2
// #define DESCRIPTION     Kimiko Rev2

// #define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
// #define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define OLED_FONT_H "keyboards/keycapsss/kimiko/keymaps/default/glcdfont.c"
// #define OLED_FONT_WIDTH 5
// #define OLED_FONT_HEIGHT 7


#ifdef RGBLIGHT_ENABLE
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
#endif

#ifdef RGB_MATRIX_ENABLE
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
	// #define RGB_MATRIX_KEYPRESSES
	// #define RGB_MATRIX_KEYRELEASES


	// These modes don’t require any additional defines.
	// #define	   ENABLE_RGB_MATRIX_NONE 
	// #define    ENABLE_RGB_MATRIX_SOLID_COLOR     // Static single hue, no speed support
	// #define    ENABLE_RGB_MATRIX_ALPHAS_MODS        // Static dual hue, speed is hue for secondary hue
	// #define    ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
	#define    ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // Full gradient scrolling left to right
	// #define    ENABLE_RGB_MATRIX_PIXEL_FRACTAL       // Single hue fractal filled keys pulsing horizontally out to edges
	// These modes also require the RGB_MATRIX_FRAMEBUFFER_EFFECTS define to be available.
	// #define    ENABLE_RGB_MATRIX_TYPING_HEATMAP      // How hot is your WPM!
	// These modes also require the RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES define to be available.
	// #define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out


	#define RGB_MATRIX_VAL_STEP 4
	#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
	#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
	#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
	#define RGB_MATRIX_DEFAULT_VAL 60 //RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
	#define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
