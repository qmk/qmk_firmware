// Copyright 2023 jpe230 (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// SPI pins
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20 // Unused

// LCD Configuration
#define LCD_RST_PIN GP21
#define LCD_CS_PIN GP8
#define LCD_DC_PIN GP9
#define LCD_BLK_PIN GP7
#define LCD_SPI_DIVISOR 4
#define LCD_WAIT_TIME 150
#define LCD_WIDTH 160
#define LCD_HEIGHT 80
#define LCD_ROTATION QP_ROTATION_270
#define LCD_OFFSET_X 1
#define LCD_OFFSET_Y 26
#define LCD_INVERT_COLOUR

// QP Configuration
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
#define ST7735_NO_AUTOMATIC_VIEWPORT_OFFSETS

// Backlight configuration
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 2

// Timeout configuration
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 10000
#define LIGHTS_TIMEOUT QUANTUM_PAINTER_DISPLAY_TIMEOUT
