// Copyright 2022 dvermd (@dvermd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// These are needed if the communication is on the SD1 USART, either with standard or alternate pins
#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

// These are needed if the communication is on the SD2 USART, either with standard or alternate pins
#undef STM32_SERIAL_USE_USART2
#define STM32_SERIAL_USE_USART2 TRUE
