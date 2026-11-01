// Copyright 2026 Andreas Hirschauer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Active-high column settling time, in microseconds.
#define MATRIX_IO_DELAY 1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

// The custom RGB Matrix driver must provide the WS2812 LED count.
#define WS2812_LED_COUNT RGB_MATRIX_LED_COUNT

// SSD1306 128x32 on I2C0 (GP0 SDA / GP1 SCL).
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1
#define OLED_DISPLAY_128X32
#define OLED_FONT_H "reform4_font.c"
#define OLED_FONT_END 255
#define OLED_TIMEOUT 10000
#define RGB_MATRIX_MODE_NAME_ENABLE
