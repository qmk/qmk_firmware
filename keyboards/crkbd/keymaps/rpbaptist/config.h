/*
This is the c configuration file for the keymap

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

/* Select hand configuration */
#define EE_HANDS

#define NO_ACTION_ONESHOT
#define NO_USB_STARTUP_CHECK

#define LAYER_STATE_8BIT // 8 layer limit

#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

#ifdef RGB_MATRIX_ENABLE

// Undefine r2g effects
#    undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#    undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_BAND_SAT
#    undef ENABLE_RGB_MATRIX_BAND_VAL
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    undef ENABLE_RGB_MATRIX_RAINDROPS
#    undef ENABLE_RGB_MATRIX_HUE_BREATHING
#    undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    undef ENABLE_RGB_MATRIX_SPLASH
#    undef ENABLE_RGB_MATRIX_SOLID_SPLASH

#    define SPLIT_TRANSACTION_IDS_USER USER_CONFIG_SYNC

#    define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define IDLE_TIMEOUT 60000 * 4
#    define GAMING_IDLE_TIMEOUT 10000
#    define RGB_MATRIX_TYPING_ACTIVE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define RGB_MATRIX_TYPING_PASSIVE RGB_MATRIX_CYCLE_ALL
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 135

#    define RGB_MATRIX_HUE_STEP 6
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 10
#    define RGB_MATRIX_SPD_STEP 10

#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP

#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses

#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

#    define RGB_MATRIX_ANIMATION_SPEED_FAST UINT8_MAX / 2
#    define RGB_MATRIX_ANIMATION_SPEED_MEDIUM UINT8_MAX / 4
#    define RGB_MATRIX_ANIMATION_SPEED_SLOW UINT8_MAX / 8
#    define RGB_MATRIX_ANIMATION_SPEED_SLOWER UINT8_MAX / 24

#    if defined(THEME_GODSPEED)
#        define THEME_HSV 132, 255, 125
#    elif defined(THEME_GODSPEED_ARES)
#        define THEME_HSV HSV_ORANGE
#    elif defined(THEME_LASER)
#        undef RGB_MATRIX_TYPING_ACTIVE
#        undef RGB_MATRIX_TYPING_PASSIVE
#        define THEME_HSV HSV_PURPLE
#        define RGB_MATRIX_TYPING_ACTIVE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define RGB_MATRIX_TYPING_PASSIVE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    elif defined(THEME_MILKSHAKE)
#        undef RGB_MATRIX_TYPING_ACTIVE
#        undef RGB_MATRIX_TYPING_PASSIVE
#        define THEME_HSV 30, 255, 218
#        define RGB_MATRIX_TYPING_ACTIVE RGB_MATRIX_TYPING_HEATMAP
#        define RGB_MATRIX_TYPING_PASSIVE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    else
#        define THEME_HSV 123, 255, 125 // default to PULSE
#    endif
#endif

#define TAPPING_TERM 140
#define PERMISSIVE_HOLD
#define TAPPING_TERM_PER_KEY

#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2

#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#    define OLED_TIMEOUT 60000 * 10
#    define OLED_FONT_H "glcdfont_multi.c"
#endif

#undef PRODUCT
#define PRODUCT "Corne Keyboard"
