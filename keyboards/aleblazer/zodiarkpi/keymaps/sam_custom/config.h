/*
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Screen support
#define ST7789_NUM_DEVICES 2
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
#define LCD_RST_PIN GP27
#define LCD_DC_PIN GP28
#define LCD_CS_PIN GP11
#define LCD_SPI_DIVISOR 8
#define QUANTUM_PAINTER_DEBUG
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS true

// Cirque support, comment out if using two screens
// #define SPLIT_POINTING_ENABLE
// #define POINTING_DEVICE_RIGHT
// #define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
// #define CIRQUE_PINNACLE_DIAMETER_MM 40
// #define CIRQUE_PINNACLE_CURVED_OVERLAY
// #define POINTING_DEVICE_CS_PIN GP11
// #define CIRQUE_PINNACLE_TAP_ENABLE
// #define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
// #define CIRQUE_PINNACLE_TAPPING_TERM 100

// RGB

// #ifdef RGBLIGHT_ENABLE
// #    define RGBLIGHT_EFFECT_BREATHING
// #    define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #    define RGBLIGHT_EFFECT_SNAKE
// #    define RGBLIGHT_EFFECT_KNIGHT
// #    define RGBLIGHT_EFFECT_CHRISTMAS
// #    define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #    define RGBLIGHT_EFFECT_RGB_TEST
// #    define RGBLIGHT_EFFECT_ALTERNATING
// #    define RGBLIGHT_EFFECT_TWINKLE
// #    define RGBLIGHT_HUE_STEP 8
// #    define RGBLIGHT_SAT_STEP 8
// #    define RGBLIGHT_VAL_STEP 8
// #    ifndef RGBLIGHT_LIMIT_VAL
// #            define RGBLIGHT_LIMIT_VAL 150
// #    endif
// #endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
// #    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
// #    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
// #    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #    define ENABLE_RGB_MATRIX_RAINDROPS
// #    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
// #    define ENABLE_RGB_MATRIX_PIXEL_RAIN
// #    define ENABLE_RGB_MATRIX_PIXEL_FLOW
// #    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL

// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #    define ENABLE_RGB_MATRIX_DIGITAL_RAIN

// enabled only if RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
// #    define RGB_MATRIX_KEYPRESSES
// #    define RGB_MATRIX_KEYRELEASES
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
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
#endif

// Tapping

#define HOLD_ON_OTHER_KEY_PRESS
#define TAPPING_TERM 175
// #define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 3000
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Space saving

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// Hardware

#define ENCODER_RESOLUTIONS {4, 2}

// Data synchronization
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_KB RPC_CAPSWORD_SYNC
