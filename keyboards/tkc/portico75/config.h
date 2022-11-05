/*
Copyright 2021 Terry Mathews

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x544B // TK
#define PRODUCT_ID      0x0011
#define DEVICE_VER      0x0001
#define MANUFACTURER    TKC
#define PRODUCT         Portico75

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS \
    { B0, E6, F0, F1, D3, D2 }
#define MATRIX_COL_PINS \
    { F4, F5, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4, D5, B3, B7 }

/*Rotary Encoder Pins*/
#define ENCODERS_PAD_A \
    { B1 }
#define ENCODERS_PAD_B \
    { B2 }

/*Sets the number of pulses per increment*/
#define ENCODER_RESOLUTION 2

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26
#    define DEBOUNCE 3
#    define RGB_DISABLE_AFTER_TIMEOUT 0     // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
// #    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
// #    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
// #    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
#    define ENABLE_RGB_MATRIX_PIXEL_FLOW
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #    define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #    define ENABLE_RGB_MATRIX_SPLASH
// #    define ENABLE_RGB_MATRIX_MULTISPLASH
// #    define ENABLE_RGB_MATRIX_SOLID_SPLASH
// #    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define DRIVER_ADDR_1 0b0110000
#    define DRIVER_COUNT 1
#    define DRIVER_1_LED_TOTAL 98
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#    define DRIVER_INDICATOR_LED_TOTAL 0
#else
// WT_RGB IS31FL3741 driver code
#    define DRIVER_COUNT 1
#    define DRIVER_LED_TOTAL 98

#    define RGB_BACKLIGHT_ENABLED 1

// This conditionally compiles the backlight code for Portico75 specifics
#    define RGB_BACKLIGHT_PORTICO75

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#    define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 1

// disable backlight after timeout in minutes, 0 = no timeout
#    define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0

// the default brightness
#    define RGB_BACKLIGHT_BRIGHTNESS 255

// the default effect (RGB test)
#    define RGB_BACKLIGHT_EFFECT 255

// the default effect speed (0-3)
#    define RGB_BACKLIGHT_EFFECT_SPEED 0

// the default color1 and color2
#    define RGB_BACKLIGHT_COLOR_1 \
        { .h = 0, .s = 255 }
#    define RGB_BACKLIGHT_COLOR_2 \
        { .h = 127, .s = 255 }

#    define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 0
#    define RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0
#    define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 0
#    define RGB_BACKLIGHT_USE_7U_SPACEBAR 0
#    define RGB_BACKLIGHT_USE_ISO_ENTER 0
#    define RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0
#    define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR \
        { .color = {.h = 0, .s = 0}, .index = 255 }
#    define RGB_BACKLIGHT_LAYER_1_INDICATOR \
        { .color = {.h = 0, .s = 0}, .index = 255 }
#    define RGB_BACKLIGHT_LAYER_2_INDICATOR \
        { .color = {.h = 0, .s = 0}, .index = 255 }
#    define RGB_BACKLIGHT_LAYER_3_INDICATOR \
        { .color = {.h = 0, .s = 0}, .index = 255 }

// These define which keys in the matrix are alphas/mods
// Used for backlight effects so colors are different for
// alphas vs. mods
// Each value is for a row, bit 0 is column 0
// Alpha=0 Mod=1
#    define RGB_BACKLIGHT_ALPHAS_MODS_ROW_0 0b0110000000000001
#    define RGB_BACKLIGHT_ALPHAS_MODS_ROW_1 0b0110000000000001
#    define RGB_BACKLIGHT_ALPHAS_MODS_ROW_2 0b0111000000000001
#    define RGB_BACKLIGHT_ALPHAS_MODS_ROW_3 0b0111100000000001
#    define RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 0b1111111111111111

// Backlight config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
#    define VIA_EEPROM_CUSTOM_CONFIG_SIZE 31

// VIA lighting is handled by the keyboard-level code
#    define VIA_CUSTOM_LIGHTING_ENABLE
#endif
