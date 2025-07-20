// Copyright 2021 azhizhinov (@azhizhinov)
// SPDX-License-Identifier: GPL-2.0-or-late
#pragma once

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
