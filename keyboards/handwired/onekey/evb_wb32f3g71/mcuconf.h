// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef WB32_ADC_USE_ADC1
#define WB32_ADC_USE_ADC1 TRUE

#undef WB32_DMA_REQUIRED
#define WB32_DMA_REQUIRED TRUE

#undef WB32_I2C_USE_I2C1
#define WB32_I2C_USE_I2C1 TRUE

#undef WB32_PWM_USE_TIM4
#define WB32_PWM_USE_TIM4 TRUE
