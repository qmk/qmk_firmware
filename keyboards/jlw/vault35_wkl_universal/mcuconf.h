// Copyright 2024 jlw
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM17
#define STM32_PWM_USE_TIM17 TRUE
#define STM32_TIM17_SUPPRESS_ISR

#define WS2812_PWM_DRIVER PWMD17
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL 1
