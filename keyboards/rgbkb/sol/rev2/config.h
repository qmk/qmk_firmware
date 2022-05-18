/*
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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0002
#define MANUFACTURER    RGBKB
#define PRODUCT         Sol

/* ws2812 RGB LED */
#define RGB_DI_PIN B7

// Underglow / DIY Tent Glow are parallel to the top row leds, no separate define
// Full Hand case adds 24 LEDs, Star Fighter case adds 38 LEDs
// For mirrored LED control (each MCU controls half the LEDs), total LED counts are divided in half
#ifdef LED_MIRRORED
  #ifdef FULLHAND_ENABLE
    #define FULLHAND_LEDS 24
    #define RGBLED_NUM 74
  #elif SF_ENABLE
    #define FULLHAND_LEDS 38
    #define RGBLED_NUM 81
  #else
    #define FULLHAND_LEDS 0
    #define RGBLED_NUM 62
  #endif
#else
  #ifdef FULLHAND_ENABLE
    #define FULLHAND_LEDS 24
    #define RGBLED_NUM 148
  #elif SF_ENABLE
    #define FULLHAND_LEDS 38
    #define RGBLED_NUM 162
  #else
    #define FULLHAND_LEDS 0
    #define RGBLED_NUM 124
  #endif
#endif

#define DRIVER_LED_TOTAL  RGBLED_NUM

#define RGB_MATRIX_CENTER { 112, 37 }

// Encoder support
#ifndef EXTRA_ENCODERS_ENABLE
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D6 }
#else
#ifdef OLED_ENABLE
    #error Extra encoders cannot be enabled at the same time as the OLED Driver as they use the same pins.
#endif
#define ENCODERS_PAD_A { D2, D1, B0 }
#define ENCODERS_PAD_B { D6, B1, D0 }
#endif
