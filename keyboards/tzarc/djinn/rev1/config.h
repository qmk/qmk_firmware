// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Split configuration
#ifdef USE_PLUG_DETECT_PIN
#    define USB_VBUS_PIN B12
#endif
#define SERIAL_USART_DRIVER SD3
#define SERIAL_USART_TX_PAL_MODE 7
#ifndef SERIAL_USART_SPEED
#    define SERIAL_USART_SPEED 640000
#endif // SERIAL_USART_SPEED

// RGB configuration
#define RGB_POWER_ENABLE_PIN B1
#define RGB_CURR_1500mA_OK_PIN B0
#define RGB_CURR_3000mA_OK_PIN C5

// EEPROM configuration
#define EEPROM_SPI_MB85RS64V
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN B5
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8 // (160MHz/8) => 20MHz
