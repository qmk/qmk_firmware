// Copyright 2023 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 16

#undef STM32_PREDIV_VALUE
#define STM32_PREDIV_VALUE 2

#undef STM32_ADC_USE_ADC2
#define STM32_ADC_USE_ADC2 TRUE

#undef STM32_ADC_USE_ADC3
#define STM32_ADC_USE_ADC3 TRUE

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE
