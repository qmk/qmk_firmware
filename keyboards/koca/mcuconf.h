/* Copyright 2025 oxnh */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

#undef STM32_PLLMUL_VALUE
#define STM32_PLLMUL_VALUE 6
