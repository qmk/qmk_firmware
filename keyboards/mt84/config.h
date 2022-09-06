 /* Copyright 2020  MT <704340378@qq.com>
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4D54  // "MT"
#define PRODUCT_ID      0x0002
#define DEVICE_VER      0x0001
#define MANUFACTURER    MT
#define PRODUCT         MT84


/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D7, D6, D5, D3, D2, D4 }
#define MATRIX_COL_PINS {B5, B6, C6, C7, F7, F6,F5, F4, F1, F0, B1, B2, B3, B7, E6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#ifdef RGB_MATRIX_ENABLE
	#define RGB_MATRIX_KEYPRESSES
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
	#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
	#define RGB_MATRIX_LED_PROCESS_LIMIT 20
	#define RGB_MATRIX_LED_FLUSH_LIMIT 26
	#define DRIVER_ADDR_1 0b1010000
	#define DRIVER_ADDR_2 0b1011111

	

    #define DRIVER_COUNT 2
	#define DRIVER_1_LED_TOTAL 44
	#define DRIVER_2_LED_TOTAL 40
	#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
	
    
    #define DISABLE_RGB_MATRIX_ALPHAS_MODS
	#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
	#define DISABLE_RGB_MATRIX_BREATHING
	#define DISABLE_RGB_MATRIX_BAND_SAT
	#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
	#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
	#define DISABLE_RGB_MATRIX_RAINDROPS
	#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
	#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
	#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
	#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
	#define DISABLE_RGB_MATRIX_SPLASH
	#define DISABLE_RGB_MATRIX_SOLID_SPLASH
	#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

#define RGB_DI_PIN B0
#ifdef RGB_DI_PIN
//    define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_BREATHING
#    define RGBLED_NUM 18
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SLEEP
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

