/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
//uncomment pieces of this section to reduce space
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif
#ifdef AUTO_SHIFT_ENABLE
#define AUTO_SHIFT_TIMEOUT 135
#endif
#ifdef RGBLIGHT_ENABLE
 #define RGBLIGHT_ANIMATIONS
  //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  //#define RGBLIGHT_EFFECT_STATIC_GRADIENT
  //#define RGBLIGHT_MODE_STATIC_LIGHT 148
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2
    #ifndef NO_DEBUG
    #define NO_DEBUG
    #endif // !NO_DEBUG
    #if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
    #define NO_PRINT
    #endif // !NO_PRINT

