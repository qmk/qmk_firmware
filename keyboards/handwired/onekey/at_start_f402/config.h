// Copyright 2023-2026 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2025 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ADC pin */
#define ADC_PIN A0

/* Backlight configs */
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 2

/* I2C 400 kHz speed */
#define I2C1_TIMINGR_PRESC 2U
#define I2C1_TIMINGR_SCLDEL 12U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 29U
#define I2C1_TIMINGR_SCLL 52U

/* LCD configs */
#define LCD_RST_PIN A2
#define LCD_DC_PIN A3
#define LCD_CS_PIN A4

/* SPI pins */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

/* Haptic configs */
#define SOLENOID_PIN B12
#define SOLENOID_PINS { B12, B13, B14, B15 }
#define SOLENOID_PINS_ACTIVE_STATE { high, high, low }
