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
#define PRODUCT_ID      0x3505
#define DEVICE_VER      0x0001
#define MANUFACTURER    RGBKB
#define PRODUCT         Pan
#define DESCRIPTION     "An universal ortho or staggered full RGB keyboard"

#ifdef PROTON_C 
  #define RGB_DI_PIN B5
#else 
  #define RGB_DI_PIN B3
#endif

/* TODO: Encoder rotation pads */
#define ENCODERS_PAD_A { 0, 0 }
#define ENCODERS_PAD_B { 0, 0 }

/* WS2812 LED handling */
#if defined(RGB_ENCODER_LEFT) && defined(RGB_ENCODER_RIGHT)
    #define RGBLED_NUM 64
#elif defined(RGB_ENCODER_LEFT) || defined(RGB_ENCODER_RIGHT)
    #define RGBLED_NUM 63
#else 
    #define RGBLED_NUM 62
#endif
#define DRIVER_LED_TOTAL RGBLED_NUM

#define RGB_MATRIX_CENTER { 114, 38 }
