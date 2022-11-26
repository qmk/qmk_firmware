// Copyright 2022 Selene ToyKeeper
// SPDX-License-Identifier: GPL-2.0-or-later
// config.h for ToyKeeper's Keyboardio Model01 layout
// (most of the config is in users/toykeeper/config.h)
#pragma once

#define KEYMAP_URL "http://toykeeper.net/keyboard/qmk/tk-model01.png"

///// personal config stuff /////

#define HAS_RGB
#undef USE_NUMPAD
#define USE_PALM  // use palm Fn keys
#define USE_TK_CLK  // locking ctrl keys
#define USE_TK_LGUI  // left GUI key has extras like right GUI
// reduce space needed, by turning off optional features
#define DONT_USE_ANY_KEY
//#define DONT_USE_TK_INFO  // I want to see the build info, even if it costs a lot of space
#define DONT_USE_EEPROM
#define DONT_USE_TK_IUUI  // kinda pointless without eeprom

#define RGB_INDICATORS_RETURN_BOOL  // define if compiling QMK newer than qmk:develop 2022-11-10 or so

// OMG THIS BOARD BOUNCES A LOT
#ifdef DEBOUNCE
#undef DEBOUNCE
#endif
#define DEBOUNCE 50  // default 2 on this board, which is bouncy AF


///// RGB stuff... /////
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-lighting

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#undef  RGB_DISABLE_WHEN_USB_SUSPENDED
//#define RGB_DISABLE_WHEN_USB_SUSPENDED 1

// disable backlight after timeout in minutes, 0 = no timeout
#define RGB_MATRIX_TIMEOUT (1000L*60*5)  // 5 minutes
#define RGB_DISABLE_TIMEOUT RGB_MATRIX_TIMEOUT

// limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// default: (DRIVER_LED_TOTAL + 4) / 5
// it uses less space without a limit
#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4)
// limits in milliseconds how frequently an animation will update the LEDs.
// 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 50  // default: 16

// reactive RGB effects
#undef RGB_MATRIX_KEYPRESSES
#undef RGB_MATRIX_KEYRELEASES

// space is tight on AVR, disable as much as possible
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP

// I like this effect, but... it makes the Model01 get laggy
// (apparently it uses too much processing power)
// TODO: find modes which are smaller and don't cause lag
//#define ENABLE_RGB_MATRIX_MULTISPLASH

//#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_MULTISPLASH

