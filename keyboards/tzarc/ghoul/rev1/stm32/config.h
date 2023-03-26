// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// Matrix configuration
#define SPI_MATRIX_CHIP_SELECT_PIN C4
#define SPI_MATRIX_DIVISOR 32

// Encoder
#define ENCODER_PUSHBUTTON_PIN C1

// SPI Configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A6
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A7
#define SPI_MISO_PAL_MODE 5

// EEPROM/Flash configuration
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 16
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN B3
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 16
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A4

// RGB configuration
#define RGB_DI_PIN C6
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 5
#define RGB_ENABLE_PIN C0

// ADC Configuration
#define ADC_RESOLUTION ADC_CFGR1_RES_12BIT
#define ADC_SATURATION ((1 << 12) - 1)
#define ADC_CURRENT_PIN C5 // ADC12_IN15
#define ADC_VOLTAGE_PIN B0 // ADC12_IN8

// Display Configuration
#define OLED_CS_PIN D2
#define OLED_DC_PIN A8
#define OLED_RST_PIN A0
