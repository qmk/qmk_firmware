 /* Copyright 2021 Dane Evans
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


//#define USE_MATRIX_I2C

/* Select hand configuration */

///https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/


#define MASTER_LEFT
// #define MASTER_RIGHT


#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_KEY_CNTR

#define TAPPING_FORCE_HOLD
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif
#define ENCODER_DIRECTION_FLIP

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SPLIT

    //#define RGBLIGHT_ANIMATIONS
	//#define RGBLIGHT_EFFECT_BREATHING
	//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	//#define RGBLIGHT_EFFECT_SNAKE
	//#define RGBLIGHT_EFFECT_KNIGHT
	//#define RGBLIGHT_EFFECT_CHRISTMAS
	#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	//#define RGBLIGHT_EFFECT_RGB_TEST
	//#define RGBLIGHT_EFFECT_ALTERNATING
	//#define RGBLIGHT_EFFECT_TWINKLE
	#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL   

#define RGBLIGHT_SLEEP

#undef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 4

#define RGB_DI_PIN D3 /* ws2812 RGB LED */

//#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+1)

    #define LEDS_HF 36
    #define RGBLIGHT_LAYERS
    #undef RGBLED_NUM
    #define RGBLED_NUM (LEDS_HF*2)
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT { LEDS_HF, LEDS_HF } 
    #undef RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_LIMIT_VAL 128

#endif

#define RGBLIGHT_MAX_LAYERS 16

