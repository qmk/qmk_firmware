/*
 *  Copyright (C) 2022  Luis Garcia
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

// Fix warning - "Attached USB accessory uses too much power."
#ifndef USB_MAX_POWER_CONSUMPTION
    #define USB_MAX_POWER_CONSUMPTION 100
#endif

// Fix unresponsive on wake from sleep
#ifndef USB_SUSPEND_WAKEUP_DELAY
    #define USB_SUSPEND_WAKEUP_DELAY 200
#endif

// Space optimizations - 01
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
//#define NO_ACTION_ONESHOT // 18016 - 17348
//#define NO_ACTION_TAPPING // 18016 - 16158

// Space optimizations - 02
#ifdef RGB_MATRIX_ENABLE
    // Remove predefined values
    #undef RGB_DISABLE_TIMEOUT
    #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef RGB_MATRIX_DEFAULT_MODE
    #undef RGB_MATRIX_DEFAULT_HUE
    #undef RGB_MATRIX_DEFAULT_SAT
    #undef RGB_MATRIX_DEFAULT_VAL

    // Redefine values
    // Number of milliseconds to wait until RGB automatically turns off
    #define RGB_DISABLE_TIMEOUT 5000
    // Limits maximum brightness of LEDs to 120 out of 255
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
    // Sets the default startup mode
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_active_keys
    // Sets the default hue, saturation & brightness values
    #define RGB_MATRIX_DEFAULT_HUE 0
    #define RGB_MATRIX_DEFAULT_SAT 0
    #define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS/3

    // Disable RGB_MATRIX_ANIMATIONS - Custom definition
    #define DISABLE_RGB_MATRIX_ANIMATIONS
    // Undefine default RGB_MATRIX_ANIMATIONS to free up space
    #undef ENABLE_RGB_MATRIX_CYCLE_ALL
    #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #undef ENABLE_RGB_MATRIX_RAINDROPS
    #undef ENABLE_RGB_MATRIX_SPLASH
    #undef ENABLE_RGB_MATRIX_MULTISPLASH
#endif  // RGB_MATRIX_ENABLE
