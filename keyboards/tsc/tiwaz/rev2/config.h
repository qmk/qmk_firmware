// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define JOY_PIN_B C2
#define JOY_PIN_X A2
#define JOY_PIN_Y A3

#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_PWM_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_PWM_DMA_CHANNEL 6

#define SERIAL_USART_DRIVER SD6
#define SERIAL_USART_TX_PAL_MODE 8
