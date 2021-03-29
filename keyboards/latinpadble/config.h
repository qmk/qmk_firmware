/*
Copyright 2021 haierwangwei2005

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#pragma once

#include "config_common.h"
#define VENDOR_ID       0x7C88 // "hw" = haierwangwei2005
#define PRODUCT_ID      0x7C98 // "lp" = latinpadble
#define DEVICE_VER      0x0001
#define MANUFACTURER    haierwangwei2005
#define PRODUCT         latinpadble

// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION



/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F0, F6, F5, F4, F1 }
#define MATRIX_COL_PINS { D6, D7, B5, B6 }
#define UNUSED_PINS

#define DIODE_DIRECTION ROW2COL

#define SSD1306OLED
#define RGB_DI_PIN B7

#define RGBLED_NUM 4
#define DRIVER_LED_TOTAL RGBLED_NUM

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5


#define RGBLIGHT_VAL_STEP 25
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 20
//#define RGBLIGHT_ANIMATIONS             // Run RGB animations
#define DISABLE_RGB_MATRIX_ALPHAS_MODS	
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN	
#define DISABLE_RGB_MATRIX_BREATHING	
#define DISABLE_RGB_MATRIX_BAND_SAT	
#define DISABLE_RGB_MATRIX_BAND_VAL	
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT	
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL	
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT	
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL	
#define DISABLE_RGB_MATRIX_CYCLE_ALL	
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT	
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN	
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN	
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL	
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON	
#define DISABLE_RGB_MATRIX_DUAL_BEACON	
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL	
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL	
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON	
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS	
#define DISABLE_RGB_MATRIX_RAINDROPS	
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS	
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP	
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS	
#define DISABLE_RGB_MATRIX_SPLASH	
#define DISABLE_RGB_MATRIX_MULTISPLASH	
#define DISABLE_RGB_MATRIX_SOLID_SPLASH	
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH	



#define OLED_FONT_H "./lib/glcdfont.c"

#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { F7 }

#define ENCODER_RESOLUTION 4
