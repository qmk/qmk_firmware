// Copyright 2020 Nick Brassel (tzarc)
// Copyright 2021 Stefan Kerkmann (@KarlK90)
// Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

#undef STM32_GPT_USE_TIM4
#define STM32_GPT_USE_TIM4 TRUE

#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 5
