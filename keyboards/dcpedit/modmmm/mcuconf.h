// Copyright 2024 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

// Used for audio
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE