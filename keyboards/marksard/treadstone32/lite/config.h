/*
Copyright 2020 marksard

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

  #ifndef IOS_DEVICE_ENABLE
    #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
    #define RGBLIGHT_VAL_STEP 8
  #else
    #define RGBLIGHT_LIMIT_VAL 50
    #define RGBLIGHT_VAL_STEP 4
  #endif

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value for treadstone32 keyboard
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif
