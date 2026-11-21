// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM15
#define STM32_PWM_USE_TIM15 TRUE

#define STM32_TIM15_SUPPRESS_ISR
