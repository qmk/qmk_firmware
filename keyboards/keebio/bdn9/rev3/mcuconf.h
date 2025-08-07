// Copyright 2025 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* enable TIM15, used for RGB LED PWM driver */
#undef STM32_PWM_USE_TIM15
#define STM32_PWM_USE_TIM15 TRUE
