// Copyright 2024 ksmosna (@ksmosna)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_HSECLK
#undef STM32_PLLSRC
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE

#define STM32_HSECLK            16000000U
#define STM32_PLLSRC            STM32_PLLSRC_HSE
#define STM32_PLLM_VALUE        16
#define STM32_PLLN_VALUE        336
#define STM32_PLLP_VALUE        4
#define STM32_PLLQ_VALUE        7
