// Copyright 2024 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* enable USART3, used for split comms */
#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

/* enable TIM3, used for RGB LED PWM driver */
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE
