// Copyright 2023-2025 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023-2025 Zhaqian <https://github.com/zhaqian12>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

// Undefine the MCU family variant.
#undef AT32F402KB

// Redefine the correct MCU family variant.
#define AT32F402RC
