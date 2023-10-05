// Copyright 2022 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 16

#undef STM32_PREDIV_VALUE
#define STM32_PREDIV_VALUE 2

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
