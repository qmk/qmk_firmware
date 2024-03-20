// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Split configuration
#define SPLIT_HAND_PIN B9
#define USB_VBUS_PIN B12
#define SERIAL_USART_DRIVER SD3
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN B10
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PIN B11
#define SERIAL_USART_RX_PAL_MODE 7
#ifndef SERIAL_USART_SPEED
#    define SERIAL_USART_SPEED 1200000
#endif // SERIAL_USART_SPEED
#define SERIAL_USART_FULL_DUPLEX

// RGB configuration
#define RGBLED_NUM 86
#define RGB_MATRIX_LED_COUNT 86
#define RGB_MATRIX_SPLIT \
    { 43, 43 }
#define RGB_POWER_ENABLE_PIN B0
#define RGB_CURR_1500mA_OK_PIN C5
#define RGB_CURR_3000mA_OK_PIN C4

// EEPROM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN B5
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8 // (160MHz/8) => 20MHz
#define EXTERNAL_EEPROM_BYTE_COUNT 8192
#define EXTERNAL_EEPROM_PAGE_SIZE 64 // it's FRAM, so it doesn't actually matter, this just sets the RAM buffer size

// External flash config
#define EXTERNAL_FLASH_SPI_MODE 3
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A8
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 4    // (160MHz/4) => 40MHz
#define EXTERNAL_FLASH_SIZE (4 * 1024 * 1024) // 32Mb/4MB capacity

// Fault indicators
#define BOARD_POWER_FAULT_PIN C9
#define RGB_POWER_FAULT_PIN C4
