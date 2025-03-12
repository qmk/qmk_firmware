// Copyright 2023-2025 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2025 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define ADC_PIN A0

#define BACKLIGHT_PWM_DRIVER PWMD5
#define BACKLIGHT_PWM_CHANNEL 1

#define LCD_RST_PIN A2
#define LCD_DC_PIN A3
#define LCD_CS_PIN A4

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

#define SOLENOID_PIN B12
#define SOLENOID_PINS { B12, B13, B14, B15 }
#define SOLENOID_PINS_ACTIVE_STATE { high, high, low }
