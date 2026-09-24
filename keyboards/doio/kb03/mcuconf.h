// Copyright (C) 2025 DOIO
// Copyright (C) 2025 ClownFish (@clownfish-og)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE
