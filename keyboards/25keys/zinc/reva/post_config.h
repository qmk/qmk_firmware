/*
Copyright 2021 monksoffunk

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

// RGB LED support
// see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SPLIT
  #ifdef RGBLED_BACK
    #ifdef RGBLED_CONT
      #define RGBLED_NUM 48
      #define RGBLED_SPLIT { 24, 24 }
    #else
      #define RGBLED_NUM 24
    #endif
  #else
    #ifdef RGBLED_BOTH
      #ifdef RGBLED_CONT
        #define RGBLED_NUM 60
        #define RGBLED_SPLIT { 30, 30 }
      #else
        #define RGBLED_NUM 30
      #endif
    #else
      #ifdef RGBLED_CONT
        #define RGBLED_NUM 12
        #define RGBLED_SPLIT { 6, 6 }
      #else
        #define RGBLED_NUM 6
      #endif
    #endif
  #endif
#endif

#ifndef IOS_DEVICE_ENABLE
  #if (RGBLED_NUM <= 6) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 12))
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #if (RGBLED_NUM <= 16) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 32))
      #define RGBLIGHT_LIMIT_VAL 130
    #else
      #define RGBLIGHT_LIMIT_VAL 120
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if (RGBLED_NUM <= 6) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 12))
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #if (RGBLED_NUM <= 16) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 32))
      #define RGBLIGHT_LIMIT_VAL 45
    #else
      #define RGBLIGHT_LIMIT_VAL 35
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif
