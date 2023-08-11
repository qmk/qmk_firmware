// Copyright 2023 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

/* Double tap reset button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#ifdef BACKLIGHT_ENABLE
#   define BACKLIGHT_PWM_DRIVER PWMD5
#   define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#endif

#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#ifdef OLED_ENABLE
#   define OLED_DISPLAY_128X64
#   define OLED_TIMEOUT 60000
#   define OLED_BRIGHTNESS 128
#endif
