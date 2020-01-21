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
#define DESCRIPTION     "An RGB, split, ortho-esque keyboard"

/* ws2812 RGB LED */
#define RGB_DI_PIN B7

#define BACKLIGHT_LEDS 124

#ifdef FULLHAND_ENABLE
  #define FULLHAND_LEDS 24
#elif SF_ENABLE
  #define FULLHAND_LEDS 38
#else
  #define FULLHAND_LEDS 0
#endif

// Underglow / DIY Tent Glow are parallel to the top row leds, no separate define

#ifdef LED_MIRRORED
  #define RGBLED_NUM ((BACKLIGHT_LEDS + FULLHAND_LEDS) / 2)
#else
  #define RGBLED_NUM (BACKLIGHT_LEDS + FULLHAND_LEDS)
#endif
#define DRIVER_LED_TOTAL  RGBLED_NUM

#define RGB_MATRIX_CENTER { 112, 37 }

// Encoder support
#ifndef EXTRA_ENCODERS_ENABLE
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D6 }
#else
#ifdef OLED_DRIVER_ENABLE
    #error Extra encoders cannot be enabled at the same time as the OLED Driver as they use the same pins.
#endif
#define ENCODERS_PAD_A { D2, D1, B0 }
#define ENCODERS_PAD_B { D6, B1, D0 }
#endif
