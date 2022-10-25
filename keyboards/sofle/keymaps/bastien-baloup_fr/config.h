 /* Copyright 2022 Bastien Baloup
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

// More lighting options in quantum/rgblight/rgblight.h
#ifdef RGBLIGHT_ENABLE

    // Disabling some of these is a good way to save flash space.
//  #define RGBLIGHT_EFFECT_ALTERNATING
//  #define RGBLIGHT_EFFECT_RGB_TEST
//  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//  #define RGBLIGHT_EFFECT_BREATHING
//  #define RGBLIGHT_EFFECT_KNIGHT
//  #define RGBLIGHT_EFFECT_SNAKE
//  #define RGBLIGHT_EFFECT_CHRISTMAS
//  #define RGBLIGHT_EFFECT_TWINKLE

    // Set default lighting option
    #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+2
    // Allow use of LEDs as modifier/layer indicators without disrupting animations.
    #define RGBLIGHT_LAYERS

    // Allow compiling to work on sofle/rev1
    #if defined(KEYBOARD_sofle_rev1)
	    #define RGBLED_NUM 70
	    // D3 for ws2812 RGB LED
	    #define RGB_DI_PIN D3
    #endif
#endif

// Disabled to save space
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE
#undef  LOCKING_SUPPORT_ENABLE
#undef  LOCKING_RESYNC_ENABLE

// Limit the number of layers that the firmware can use to save space
#define LAYER_STATE_8BIT
