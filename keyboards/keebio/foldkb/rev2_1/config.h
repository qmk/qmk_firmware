// Copyright 2025 Keebio (@keebio)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Defines for the split keyboard setup */
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_PIN_SWAP

#define USB_VBUS_PIN A7

/* Defines for the RGB matrix */
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 3
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP
