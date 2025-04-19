// Copyright 2025 Erik Dietrich (@iH0118)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS                         10
#define MATRIX_COLS                         6

//#define WS2812_POWER_ENABLE_PIN             A5
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_DRIVER                   PWMD2
#define WS2812_PWM_CHANNEL                  1
#define WS2812_PWM_PAL_MODE                 5
#define WS2812_PWM_DMA_STREAM	            STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL              8

#define RGB_MATRIX_DEFAULT_MODE             RGB_MATRIX_MULTISPLASH
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD    25

#define USB_VBUS_PIN                        A9
#define SPLIT_TRANSPORT_MIRROR
#define EE_HANDS

#define STM32_ONBOARD_EEPROM_SIZE           (6*1024)

#define SERIAL_USART_DRIVER                 SD2
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN                 A2
#define SERIAL_USART_TX_PAL_MODE            4
#define SERIAL_USART_RX_PIN                 A3
#define SERIAL_USART_RX_PAL_MODE            4

