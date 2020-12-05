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
#define DEVICE_VER      0x0001
#define MANUFACTURER    RGBKB
#define PRODUCT         Sol
#define DESCRIPTION     "An RGB, split, ortho-esque keyboard"

/* ws2812 RGB LED */
#define RGB_DI_PIN B3

#ifdef LED_MIRRORED
  #define RGBLED_NUM 35
#else
  #define RGBLED_NUM 70
#endif
#define DRIVER_LED_TOTAL  RGBLED_NUM

#define RGB_MATRIX_CENTER { 112, 35 }

// Encoder support
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D6 }
