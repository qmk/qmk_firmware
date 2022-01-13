// Copyright 2022 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VENDOR_ID       0x594D
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    YMDK
#define PRODUCT         Split75

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 14

#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D1
#define LED_SCROLL_LOCK_PIN D6

#define RGBLED_NUM 8
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP

#define BACKLIGHT_PIN D4

#define I2C_START_RETRY_COUNT 1