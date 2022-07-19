// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

// Used for audio
#undef STM32_PWM_USE_TIM1
#undef STM32_GPT_USE_TIM6
#undef STM32_GPT_USE_TIM7
#undef STM32_GPT_USE_TIM8
#define STM32_PWM_USE_TIM1 TRUE
#define STM32_GPT_USE_TIM6 TRUE
#define STM32_GPT_USE_TIM7 TRUE
#define STM32_GPT_USE_TIM8 TRUE

// Used for backlight
#undef STM32_PWM_USE_TIM17
#define STM32_PWM_USE_TIM17 TRUE

// Used for SK6812 chain
#undef STM32_PWM_USE_TIM20
#define STM32_PWM_USE_TIM20 TRUE

// Used for split comms
#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

// Used for EEPROM/LCD
#undef STM32_SPI_USE_SPI3
#define STM32_SPI_USE_SPI3 TRUE
