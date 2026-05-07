/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 14
