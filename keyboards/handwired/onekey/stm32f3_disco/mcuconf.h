// Copyright 2023 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef STM32_SIO_USE_USART1
#define STM32_SIO_USE_USART1 TRUE

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
