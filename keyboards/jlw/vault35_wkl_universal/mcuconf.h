// Copyright 2024 jlw
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM17
#define STM32_PWM_USE_TIM17 TRUE
#define STM32_TIM17_SUPPRESS_ISR

