// Copyright 2019 astro <yuleiz@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 192

#undef STM32_PPRE2
#define STM32_PPRE2 STM32_PPRE2_DIV2
