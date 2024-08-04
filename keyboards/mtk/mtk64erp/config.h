// Copyright 2024 mentako-ya
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define MATRIX_MASKED
#define DEBOUNCE 5

#define SPLIT_HAND_MATRIX_GRID  GP21, GP23
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT
#define SPLIT_MAX_CONNECTION_ERRORS 10
#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#define SPLIT_LAYER_STATE_ENABLE

#define USB_POLLING_INTERVAL_MS 1
#define F_SCL 400000UL

#ifdef POINTING_DEVICE_ENABLE
// Trackball  parameters
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN GP14
#    define SPI_MISO_PIN GP12
#    define SPI_MOSI_PIN GP15
#    define PMW33XX_CS_PIN GP13
#    define POINTING_DEVICE_CS_PIN GP13
#    define MOUSE_EXTENDED_REPORT

#    define SPLIT_POINTING_ENABLE
#    define POINTING_DEVICE_TASK_THROTTLE_MS 0
//#    define POINTING_DEVICE_LEFT
#    define POINTING_DEVICE_RIGHT
//#    define POINTING_DEVICE_COMBINED

#ifdef CONSOLE_ENABLE
#    define POINTING_DEVICE_DEBUG
#endif

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE   // Enables auto mouse layer feature
#define AUTO_MOUSE_DEFAULT_LAYER 7          // Index of layer to use as default target layer
#define AUTO_MOUSE_TIME 1000                // Time layer remains active after activation
#define AUTO_MOUSE_THRESHOLD 200            // Amount of mouse movement required to switch layers
#endif

#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#ifdef OLED_ENABLE
#   define OLED_DISPLAY_128X64
#   define OLED_TIMEOUT 60000
#   define OLED_BRIGHTNESS 128
#   define OLED_SCROLL_TIMEOUT 0
#ifndef OLED_FONT_H
#   define OLED_FONT_H "keyboards/mtk/mtk64erp/glcdfont.c"
#endif
#endif

#ifdef RGBLIGHT_ENABLE
  #define WS2812_DI_PIN GP0
  #undef RGBLIGHT_LED_COUNT
  #define RGBLIGHT_LED_COUNT 14
  #undef RGBLED_SPLIT
  #define RGBLED_SPLIT {7, 7}

  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_EFFECT_CHRISTMAS
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_EFFECT_RGB_TEST
  #define RGBLIGHT_EFFECT_ALTERNATING
  #define RGBLIGHT_EFFECT_TWINKLE
#endif
