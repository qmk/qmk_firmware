// Copyright 2023 Isaac Rex (@Isaac Rex)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define EECONFIG_KB_DATA_SIZE 11

// Setup for RGB Matrix 
#define RGB_MATRIX_LED_COUNT 33
#define WS2812_DI_PIN GP19

// RGB Matrix Enabled Effects
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

// RGB Matrix Parameters
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_BREATHING // Sets the default mode, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255

#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 0 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES