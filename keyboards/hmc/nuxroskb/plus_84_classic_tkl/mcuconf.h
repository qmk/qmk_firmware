// Copyright 2026 HMC Studio
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV2
