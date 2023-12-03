// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_VCC

#define DRIVER_1_LED_TOTAL 36
#define DRIVER_2_LED_TOTAL 36
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#ifndef ISSI_TIMEOUT
#    define ISSI_TIMEOUT 5
#endif

#define MOUSEKEY_WHEEL_INTERVAL MOUSEKEY_INTERVAL
#define MOUSEKEY_WHEEL_MAX_SPEED MOUSEKEY_MAX_SPEED
#define MOUSEKEY_WHEEL_TIME_TO_MAX MOUSEKEY_TIME_TO_MAX

// Delay between each i2c io expander ops (in MCU cycles)
#define IO_EXPANDER_OP_DELAY 500
