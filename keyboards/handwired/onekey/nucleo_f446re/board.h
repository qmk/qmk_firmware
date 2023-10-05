// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <board.h>

#undef STM32_HSECLK
#define STM32_HSECLK 8000000U
#define STM32_HSE_BYPASS
