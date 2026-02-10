// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

// Used for SK6812 chain
#undef STM32_PWM_USE_TIM17
#define STM32_PWM_USE_TIM17 TRUE

// Used for NOR Flash
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE
