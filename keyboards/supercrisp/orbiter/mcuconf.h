// Copyright 2026 Karl Stralman (@kjeller)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE

#define STM32_I2C_I2C2_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 5)
#define STM32_I2C_I2C2_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 4)
