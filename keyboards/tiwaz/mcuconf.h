// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 25

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 336

#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE 4

#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE 7

#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE

#undef STM32_SERIAL_USE_USART6
#define STM32_SERIAL_USE_USART6 TRUE
