// Copyright 2023-2024 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2024 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ADC configs */
#define ADC_PIN C5
#define ADC_USE_ADC1

/* SPI configs */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

/* I2C configs */
#define USE_I2CV1_CONTRIB
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PIN B6
#define I2C1_SCL_PAL_MODE 4
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 100000

/* Apa102 configs */
#define APA102_NOPS (100 / (1000000000L / (CPU_CLOCK / 4)))

/* Haptic configs */
#define SOLENOID_PIN B12
#define SOLENOID_PINS { B12, B13, B14, B15 }
#define SOLENOID_PINS_ACTIVE_STATE { high, high, low }

/* Backlight configs */
#define BACKLIGHT_PWM_DRIVER PWM_GP16C4T1
#define BACKLIGHT_PWM_CHANNEL 3

/* LCD configs */
#define LCD_RST_PIN A2
#define LCD_DC_PIN A3
#define LCD_CS_PIN A4

// Bitbang WS2812
#define WS2812_BITBANG_NOP_FUDGE 0.4
