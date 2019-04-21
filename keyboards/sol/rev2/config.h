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

#define DIY_BACKLIGHT_ENABLE
#define FULLHAND_ENABLE

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0002
#define MANUFACTURER    RGBKB
#define PRODUCT         Sol
#define DESCRIPTION     "An RGB, split, ortho-esque keyboard"

#define KEY_BACKLIGHT_LEDS 70

#ifdef DIY_BACKLIGHT_ENABLE
  #define DIY_BACKLIGHT_LEDS 54
#else
  #define DIY_BACKLIGHT_LEDS 0
#endif

#ifdef FULLHAND_ENABLE
  #define FULLHAND_LEDS 48
#else
  #define FULLHAND_LEDS 0
#endif

// TODO: Have not tried LED_MIRRORED + RGB_MATRIX
#ifdef LED_MIRRORED
  #define RGBLED_NUM ((KEY_BACKLIGHT_LEDS + DIY_BACKLIGHT_LEDS + FULLHAND_LEDS) / 2)
#else
  #define RGBLED_NUM (KEY_BACKLIGHT_LEDS + DIY_BACKLIGHT_LEDS + FULLHAND_LEDS)
#endif
#define DRIVER_LED_TOTAL  RGBLED_NUM
