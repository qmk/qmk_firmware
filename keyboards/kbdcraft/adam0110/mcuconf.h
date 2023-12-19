// Copyright 2023 FxStudio <FXS@fx-studio.cn>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_ADVANCED
#define STM32_PWM_USE_ADVANCED TRUE

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
