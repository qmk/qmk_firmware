// Copyright 2022 ZyBeR (@ZyberSE)
// SPDX-License-Identifier: GPL-2.0

#pragma once

/**
 * Enable/disable LEDs based on layout
 */
#undef RGB_BACKLIGHT_USE_SPLIT_BACKSPACE
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 0


/**
 * Switch off Backlight when computer is suspended
 */
#undef RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED
#define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 1


/**
 * Use http://colorizer.org/ to get a 0-360 hue value
 * then convert it into a 0-255 value with n = (hue / 360 * 255).
 */
#undef RGB_BACKLIGHT_CAPS_LOCK_INDICATOR
#define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR { .color = { .h = 255, .s = 255 }, .index = 254 }
#undef RGB_BACKLIGHT_LAYER_1_INDICATOR
#define RGB_BACKLIGHT_LAYER_1_INDICATOR { .color = { .h = 87, .s = 255 }, .index = 254 }
#undef RGB_BACKLIGHT_LAYER_2_INDICATOR
#define RGB_BACKLIGHT_LAYER_2_INDICATOR { .color = { .h = 167, .s = 255 }, .index = 254 }
#undef RGB_BACKLIGHT_LAYER_3_INDICATOR
#define RGB_BACKLIGHT_LAYER_3_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
