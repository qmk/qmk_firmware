// Copyright 2023 Daniel Reibl (@riblee)
// SPDX-License-Identifier: GPL-2.0-or-later

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
