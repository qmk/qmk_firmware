// Copyright 2026 rkey-device
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

/* 12 MHz crystal on board */
#undef STM32_PLLMUL_VALUE
#define STM32_PLLMUL_VALUE		6
