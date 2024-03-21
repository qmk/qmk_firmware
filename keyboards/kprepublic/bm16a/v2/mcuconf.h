// Copyright 2022 fauxpark (@fauxpark)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE
