// Copyright 2025 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// Used for RGB matrix
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE

// Used for audio
#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

// Used for audio
#undef STM32_GPT_USE_TIM5
#define STM32_GPT_USE_TIM5 TRUE

// Used for FRAM
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
