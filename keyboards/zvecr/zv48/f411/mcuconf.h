// Copyright 2024 zvecr <git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
