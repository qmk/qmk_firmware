/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_I2C_USE_DMA
#define STM32_I2C_USE_DMA TRUE

#define STM32_I2C_BUSY_TIMEOUT 50
#define STM32_I2C_I2C1_IRQ_PRIORITY 3
#define STM32_I2C_I2C1_DMA_PRIORITY 1
#define STM32_I2C_DMA_ERROR_HOOK(i2cp) osalSysHalt("DMA failure")
#undef STM32_I2C_I2C1_RX_DMA_STREAM
#define STM32_I2C_I2C1_RX_DMA_STREAM STM32_DMA_STREAM_ID(1, 3)
#undef STM32_I2C_I2C1_TX_DMA_STREAM
#define STM32_I2C_I2C1_TX_DMA_STREAM STM32_DMA_STREAM_ID(1, 2)

#undef STM32_GPT_USE_TIM14
#define STM32_GPT_USE_TIM14 TRUE
#define STM32_TIM14_SUPPRESS_ISR
