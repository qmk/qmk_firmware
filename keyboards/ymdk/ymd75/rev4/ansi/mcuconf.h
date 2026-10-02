// Copyright 2020 QMK
// Copyright 2026 Steffen Olszewski (@sodevel)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8
