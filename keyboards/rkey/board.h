// Copyright 2026 rkey-device
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <board.h>

#undef STM32_HSECLK
#define STM32_HSECLK        12000000U

// #define STM32_LSE_ENABLED   FALSE
