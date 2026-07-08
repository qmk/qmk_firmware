// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8

#undef STM32_PLLSAIM_VALUE
#define STM32_PLLSAIM_VALUE 8
