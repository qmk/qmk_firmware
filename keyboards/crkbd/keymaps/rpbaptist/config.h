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

//#define USE_MATRIX_I2C

/* Select hand configuration */
#define EE_HANDS

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 600000
#endif

// #define FORCE_NKRO

#define QMK_ESC_OUTPUT F4  // usually COL
#define QMK_ESC_INPUT D4   // usually ROW
#define QMK_LED B0

#define NO_ACTION_ONESHOT

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 12
#    define RGB_MATRIX_VAL_STEP 10
#    define RGB_MATRIX_SPD_STEP 10

#    undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#    undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    undef ENABLE_RGB_MATRIX_BREATHING
#    undef ENABLE_RGB_MATRIX_BAND_SAT
#    undef ENABLE_RGB_MATRIX_BAND_VAL
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL

// #undef ENABLE_RGB_MATRIX_CYCLE_ALL
// #    undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    undef ENABLE_RGB_MATRIX_DUAL_BEACON
#    undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    undef ENABLE_RGB_MATRIX_RAINDROPS
#    undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

#    undef ENABLE_RGB_MATRIX_SPLASH
#    undef ENABLE_RGB_MATRIX_MULTISPLASH
#    undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#    undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_ANIMATION_SPEED_DEFAULT UINT8_MAX / 2
#    define RGB_MATRIX_ANIMATION_SPEED_SLOW RGB_MATRIX_ANIMATION_SPEED_DEFAULT / 4
#    define RGB_MATRIX_ANIMATION_SPEED_SLOWER RGB_MATRIX_ANIMATION_SPEED_SLOW / 3
#endif

#define TAPPING_TERM 140
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE 2

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 36
#    define MOUSEKEY_WHEEL_MAX_SPEED 4
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 100
#endif

#ifdef THEME_GODSPEED
#   define OLED_FONT_H "keyboards/crkbd/keymaps/rpbaptist/glcdfont_godspeed.c"
#   define THEME_HSV 132, 255, 125
#endif

#ifdef THEME_PULSE
#   define OLED_FONT_H "keyboards/crkbd/keymaps/rpbaptist/glcdfont_pulse.c"
#   define THEME_HSV 123, 255, 125
#endif

#ifdef THEME_LASER
#   define OLED_FONT_H "keyboards/crkbd/keymaps/rpbaptist/glcdfont_laser.c"
#   define THEME_HSV HSV_MAGENTA
#endif

#define NO_ACTION_ONESHOT

#undef PRODUCT
#define PRODUCT "Corne Keyboard"

#define LCPC_KEYS KC_LCTL, KC_LSFT, KC_9
#define RCPC_KEYS KC_RCTL, KC_RSFT, KC_0
