/* Copyright 2024 Simon Major (@majorsimon)
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
#define MASTER_LEFT

#define CUSTOM_FONT
#define DYNAMIC_KEYMAP_LAYER_COUNT 12

#define QUICK_TAP_TERM 0
#ifdef TAPPING_TERM
  #undef TAPPING_TERM
  #define TAPPING_TERM 200
#endif

#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding
#define USB_MAX_POWER_CONSUMPTION 500
/* ws2812 RGB LED */
#define WS2812_DI_PIN D3


#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LAYERS
  #undef RGBLED_NUM

  #define RGBLED_NUM 72
	#define RGBLED_SPLIT { 36, 36 } // haven't figured out how to use this yet

	//#define RGBLED_NUM 30
  #define RGBLIGHT_LIMIT_VAL 120
  #define RGBLIGHT_HUE_STEP 10
  #define RGBLIGHT_SAT_STEP 17
  #define RGBLIGHT_VAL_STEP 17
#endif 

#ifdef RGB_MATRIX_ENABLE

  #define RGB_MATRIX_LED_COUNT 72
  #define RGB_MATRIX_SPLIT { 36, 36 }
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. Higher may cause the controller to crash.
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS_INDICATOR 30 // limits maximum brightness of indicator LEDs to 30 out of 255. Higher may cause the controller to crash.
  
  #define RGB_MATRIX_DEFAULT_ON true
  #define RGB_MATRIX_DEFAULT_HUE 234
  #define RGB_MATRIX_DEFAULT_SAT 254
  #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS

  #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_BREATHING
  #define ENABLE_RGB_MATRIX_RIVERFLOW
  #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  #define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
  #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
  #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RIVERFLOW
  #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_DEFAULT_MODE

  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10
#endif


// Encoder support
#define ENCODER_DIRECTION_FLIP
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTIONS { 4 } //Left encoder seems to have double-output issue but right does not. This resolves that issue.


// OLED settings
#ifdef OLED_ENABLE
  #define SPLIT_LAYER_STATE_ENABLE
  #define SPLIT_TRANSPORT_MIRROR
	#define OLED_TIMEOUT 120000			//80000 = 80secs, 120000 = 2mins in ms.
	#define OLED_BRIGHTNESS 90			//Default is 100.
	#define SPLIT_OLED_ENABLE			//Synx on/off OLED state between halves (+100).
	#ifdef WPM_ENABLE
		#define SPLIT_WPM_ENABLE			//Enable WPM across split keyboards (+106-268).
	#endif
	#ifdef OLED_NO_MASTER
		#define SPLIT_LAYER_STATE_ENABLE	//Keep on master to save space (+142).
		#define SPLIT_LED_STATE_ENABLE		//Keep on master to save space (+112).
		#undef SPLIT_OLED_ENABLE			//Do not sync OLED state with one OLED only (+100).
	#endif
	//#define SPLIT_MODS_ENABLE			//Keep on master to save space (+138).
#endif
