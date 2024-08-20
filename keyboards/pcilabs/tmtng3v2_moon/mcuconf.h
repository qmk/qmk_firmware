/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include_next <mcuconf.h>

#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

// #undef STM32_ADC_USE_ADC2
// #define STM32_ADC_USE_ADC2 TRUE

// #define STM32_ADC_ADC1_DMA_STREAM           STM32_DMA_STREAM_ID(1, 1)
// #define STM32_ADC_ADC2_DMA_STREAM           STM32_DMA_STREAM_ID(2, 1)
// #define STM32_ADC_ADC4_DMA_STREAM           STM32_DMA_STREAM_ID(2, 2)

// #undef STM32_PWM_USE_ADVANCED
// #define STM32_PWM_USE_ADVANCED      TRUE

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

/*
// #define STM32_HSE_BYPASS
#undef STM32_HSECLK
#define STM32_HSECLK 16000000U
#undef  STM32_PREDIV_VALUE
#define STM32_PREDIV_VALUE          2
#undef  STM32_PPRE2
#define STM32_PPRE2                 STM32_PPRE2_DIV1
*/
