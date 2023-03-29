// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// Matrix configuration
#define SPI_MATRIX_CHIP_SELECT_PIN GP21
#define SPI_MATRIX_DIVISOR 16

// Encoder
#define ENCODER_PUSHBUTTON_PIN GP7

// SPI Configuration
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20

// EEPROM configuration
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN GP3
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 8
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN GP2

// RGB configuration
#define RGB_DI_PIN GP13
#define RGB_ENABLE_PIN GP6

// ADC Configuration
#define ADC_RESOLUTION 12
#define ADC_SATURATION ((1 << 12) - 1)
#define ADC_CURRENT_PIN GP26
#define ADC_VOLTAGE_PIN GP27

// Display Configuration
#define OLED_CS_PIN GP16
#define OLED_DC_PIN GP17
#define OLED_RST_PIN GP18
