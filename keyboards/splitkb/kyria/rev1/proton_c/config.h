// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SERIAL_USART_FULL_DUPLEX      // Enable full duplex operation mode.
#define SERIAL_USART_PIN_SWAP         // Swap TX and RX pins if keyboard is master halve.
#define SERIAL_USART_DRIVER      SD1  // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7    // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TX_PIN      A9
#define SERIAL_USART_RX_PIN      A10

#define WS2812_PWM_CHANNEL     4
#define WS2812_PWM_PAL_MODE    1
#define WS2812_PWM_DMA_STREAM  STM32_DMA1_STREAM2     // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_PWM_DMA_CHANNEL 2                      // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_PWM_DMAMUX_ID   STM32_DMAMUX1_TIM2_UP  // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.
