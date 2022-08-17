// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Limit the backlight brightness
#ifndef BACKLIGHT_LIMIT_VAL
#    define BACKLIGHT_LIMIT_VAL 144
#endif // BACKLIGHT_LIMIT_VAL

// Split configuration
#define SPLIT_HAND_PIN B11
#ifdef USE_PLUG_DETECT_PIN
#    define USB_VBUS_PIN B12
#endif
#define SERIAL_USART_DRIVER SD3
#define SERIAL_USART_TX_PAL_MODE 7
#define SOFT_SERIAL_PIN B9
#ifndef SERIAL_USART_SPEED
#    define SERIAL_USART_SPEED 640000
#endif // SERIAL_USART_SPEED

// RGB configuration
#define RGBLED_NUM 84
#define DRIVER_LED_TOTAL 84
#define RGB_MATRIX_SPLIT \
    { 42, 42 }
#define RGB_POWER_ENABLE_PIN B1
#define RGB_CURR_1500mA_OK_PIN B0
#define RGB_CURR_3000mA_OK_PIN C5

// EEPROM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN B5
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8 // (160MHz/8) => 20MHz
#define EXTERNAL_EEPROM_BYTE_COUNT 8192
#define EXTERNAL_EEPROM_PAGE_SIZE 64 // it's FRAM, so it doesn't actually matter, this just sets the RAM buffer size
