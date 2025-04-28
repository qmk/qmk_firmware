// Copyright 2023-2025 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2025 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef AT32_ADC_USE_ADC1
#define AT32_ADC_USE_ADC1 TRUE

#undef AT32_I2C_USE_I2C1
#define AT32_I2C_USE_I2C1 TRUE

#undef AT32_PWM_USE_TMR5
#define AT32_PWM_USE_TMR5 TRUE
