// Copyright 2026 Timo Strube (@tstrube)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <board.h>

#undef STM32_HSECLK
#define STM32_HSECLK 25000000U
