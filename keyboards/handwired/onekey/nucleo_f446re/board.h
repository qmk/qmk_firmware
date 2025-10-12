// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <board.h>

// Configure clocks to use onboard STLINKs MCO as HSE is not populated by default
#define STM32_HSE_BYPASS
